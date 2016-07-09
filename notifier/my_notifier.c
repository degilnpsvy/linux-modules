#include <linux/notifier.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");

#define TESTCHAIN_INIT 0x52U
static RAW_NOTIFIER_HEAD(test_chain);

/* define our own notifier_call_chain */
static int call_test_notifiers(unsigned long val, void *v)
{
    return raw_notifier_call_chain(&test_chain, val, v);
}
EXPORT_SYMBOL(call_test_notifiers);

/* define our own notifier_chain_register func */
static int register_test_notifier(struct notifier_block *nb)
{
    int err;
    err = raw_notifier_chain_register(&test_chain, nb);
    if(err)
        goto out;
 out:
    return err;
}
EXPORT_SYMBOL(register_test_notifier);

static int __init my_notifier_init(void)
{
	printk(KERN_EMERG "my_notifier_init\n");

	return 0;
}

static void __exit my_notifier_exit(void)
{
	printk(KERN_EMERG "my_notifier_exit\n");
	return;
}

module_init(my_notifier_init);
module_exit(my_notifier_exit);
