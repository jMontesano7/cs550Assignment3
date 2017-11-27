#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

MODULE_LICENSE("DUAL BSD/GPL");


int __init init_module(void);
static ssize_t my_read(struct file *file, char __user *out, size_t size, loff_t *off);
static int my_open(struct inode *inode, struct file *file);
static int my_close(struct inode *inodep, struct file *filp);
static ssize_t my_write(struct file *file, char __user *out, size_t size, loff_t *off);

static struct file_operations my_fops = {
.owner = THIS_MODULE,
.open = my_open,
.release = my_close,
.read = my_read,
.write = my_write,
};

static struct miscdevice my_time = {
.minor = MISC_DYNAMIC_MINOR,
.name = "numpipe",
.fops = &my_fops
};

static int N = 4;
module_param(N, int, S_IRUGO);
static DEFINE_SEMAPHORE(semReadable);
static DEFINE_SEMAPHORE(semWriteable);
static DEFINE_MUTEX(mut);
int * pipeData;
int lastDataSpot = 0;
int __init init_module()
{
	printk(KERN_ALERT "THIS IS WORKING AND READING");
	//return -1;  TEST
	if(misc_register(&my_time) != 0)
	{
		printk(KERN_ALERT "HEY ISsUE WITH REG");
		return -1;
	}
	else
	{
		printk(KERN_ALERT "N = %d ",N);
		sema_init(&semReadable,0);
		sema_init(&semWriteable,N);
		mutex_init(&mut);
		pipeData = (int*)vmalloc(sizeof(int)*N);
		if(pipeData == NULL)
		{

			printk(KERN_ALERT "ISSUE----------------");
			return -1;
		}
		return 0;


	}
}

void __exit my_exit(void)
{
	misc_deregister(&my_time);
	return 0;
}
static ssize_t my_read(struct file *file, char __user *out, size_t size, loff_t *off)
{
	down_interruptible(&semReadable);
	mutex_lock_interruptible(&mut);
	
	int buff = pipeData[0];
	int i = 0;
	for(i = 0; i < lastDataSpot; i++)
	{
		pipeData[i] =pipeData[i+1]; 
	}
	lastDataSpot--;
	mutex_unlock(&mut);
	up(&semWriteable);
	
	if(copy_to_user(out, &buff, sizeof(buff)))
	{
		return -1;
	}	
	return sizeof(buff);
}
static ssize_t my_write(struct file *file, char __user *out, size_t size, loff_t *off)
{
	int buff;
	if(copy_from_user(&buff, out, sizeof(buff)))
	{

		printk(KERN_ALERT "my_xtime: COPY FROM USER FAILURE!\n");
		return -EFAULT;
	}

	//Try to acquire critical section
	if(lastDataSpot == -1)
		lastDataSpot = 0;

	printk(KERN_ALERT "WRITING TO : %d",lastDataSpot);
	down_interruptible(&semWriteable);
	mutex_lock_interruptible(&mut);

	pipeData[lastDataSpot]=buff;	
	lastDataSpot++;

	mutex_unlock(&mut);
	up(&semReadable);
	return sizeof(buff);
}
static int my_open(struct inode *inode, struct file *file)
{
	return 0;
}
static int my_close(struct inode *inodep, struct file *filp)
{
	return 0;
}

