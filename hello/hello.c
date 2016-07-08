
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static int num=0;
module_param(num,int,S_IRUGO);
static int __init hello_init(void)
{
	printk(KERN_EMERG "hello_init\n");
	printk(KERN_EMERG "num=%d\n",num);
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_EMERG "hello_exit\n");
	return;
}

module_init(hello_init);
module_exit(hello_exit);
