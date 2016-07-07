#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");

static void work_handler(struct work_struct *data)
{
    printk(KERN_ALERT "work handler function\n");
}
static struct work_struct work;

static int __init try_workqueue_init(void)
{
	printk(KERN_EMERG "try_workqueue_init\n");
        INIT_WORK(&work,work_handler);
        schedule_work(&work);
	return 0;
}

static void __exit try_workqueue_exit(void)
{
	printk(KERN_EMERG "try_workqueue_exit\n");
	return;
}

module_init(try_workqueue_init);
module_exit(try_workqueue_exit);
