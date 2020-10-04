#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ivan Petrov");
MODULE_DESCRIPTION("just a dummy");
MODULE_VERSION("0.01");

static int __init dummy_init(void){
	printk(KERN_INFO "Hello, World!\n");
	return 0;
}
static void __exit dummy_exit(void){
	printk(KERN_INFO "Goodbye, World!\n");
}
module_init(dummy_init);
module_exit(dummy_exit);