#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xdb68a6ee, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xea290159, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x601f590e, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x8e88c094, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xe14298ee, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x78e739aa, __VMLINUX_SYMBOL_STR(up) },
	{ 0x3970fbc1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x1ddd1cea, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x6dc0c9dc, __VMLINUX_SYMBOL_STR(down_interruptible) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "40E97FD2B6EEBA7A69D8CA6");
