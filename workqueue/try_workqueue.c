#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");

static struct workqueue_struct *wq;
static int a=0;

static void work_handler(struct work_struct *data)
{
    printk(KERN_ALERT "work handler function%d\n",a++);
}
static struct work_struct work;

static int __init try_workqueue_init(void)
{
	printk(KERN_EMERG "try_workqueue_init\n");
        wq=create_singlethread_workqueue("my_singlethread_workqueue");
        INIT_WORK(&work,work_handler);
        queue_work(wq,&work);
        queue_work(wq,&work);
        printk(KERN_EMERG "try_workqueue flush before\n");
        flush_workqueue(wq);
        printk(KERN_EMERG "try_workqueue flush after\n");
        queue_work(wq,&work);
	return 0;
}

static void __exit try_workqueue_exit(void)
{
	printk(KERN_EMERG "try_workqueue_exit\n");
	return;
}

module_init(try_workqueue_init);
module_exit(try_workqueue_exit);
