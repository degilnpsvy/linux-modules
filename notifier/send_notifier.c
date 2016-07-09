#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

extern int call_test_notifiers(unsigned long val, void *v);
#define TESTCHAIN_INIT 0x52U

static int __init send_notifer_init(void)
{
    printk(KERN_EMERG "send_notifer_init\n");
    call_test_notifiers(TESTCHAIN_INIT, "no_use");

    return 0;
}

static void __exit send_notifer_exit(void)
{
    printk(KERN_EMERG "send_notifer_exit\n");
}


MODULE_LICENSE("GPL");

module_init(send_notifer_init);
module_exit(send_notifer_exit);
