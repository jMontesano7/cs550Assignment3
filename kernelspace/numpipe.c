#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

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

const int N = 100;
static DEFINE_SEMAPHORE(semReadable);
static DEFINE_SEMAPHORE(semWriteable);
static DEFINE_MUTEX(mut);


int __init init_module()
{
	//return -1;  TEST
	if(misc_register(&my_time) != 0)
	{
		return -1;
	}
	else
	{
		sema_init(&semReadable,0);
		sema_init(&semWriteable,N);
		mutex_init(&mut);

		return 0;

	}
}

void __exit my_exit(void)
{
	misc_deregister(&my_time);
}
static ssize_t my_read(struct file *file, char __user *out, size_t size, loff_t *off)
{
	return 0;
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

	down_interruptible(&semWriteable);
	mutex_lock_interruptible(&mut);
	

	mutex_unlock(&mut);
	up(&semReadable);
	return 0;
}
static int my_open(struct inode *inode, struct file *file)
{
	return 0;
}
static int my_close(struct inode *inodep, struct file *filp)
{
	return 0;
}
