#include <linux/kernel.h>
#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

extern int register_test_notifier(struct notifier_block *nb);
#define TESTCHAIN_INIT 0x52U

/* realize the notifier_call func */
int test_init_event(struct notifier_block *nb, unsigned long event, void *v)
{
    switch(event)
    {
    case TESTCHAIN_INIT:
        printk(KERN_EMERG "In get_notifier: got that send_notifier init\n");
        break;
    default:
        break;
    }
    return NOTIFY_DONE;
}

/* define a notifier_block */
static struct notifier_block test_init_notifier= {
    .notifier_call = test_init_event,
};

static int __init get_notifier_init(void)
{
    printk(KERN_EMERG "get_notifier_init\n");
    register_test_notifier(&test_init_notifier);
    return 0;
}

static void __exit get_notifier_exit(void)
{
    printk(KERN_EMERG "get_notifier_exit\n");
}

MODULE_LICENSE("GPL");

module_init(get_notifier_init);
module_exit(get_notifier_exit);
