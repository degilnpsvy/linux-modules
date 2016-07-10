#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");
struct my_data
{
    struct kref refcount;
    int num;
};

void data_release(struct kref *ref)
{
    struct my_data * data=container_of(ref,struct my_data, refcount);
    kfree(data);
}

int more_data_handling(void *cb_data)
{
    struct my_data *data=cb_data;
    data->num++;
    printk(KERN_EMERG "End of more_data_handling %d\n", data->num);
    kref_put(&data->refcount,data_release);
    return 0;
}

int my_data_handler(void)
{
    int rv=0;
    struct my_data *data;
    struct task_struct *task;
    data=kmalloc(sizeof(*data), GFP_KERNEL);
    if (!data)
        return -ENOMEM;
    data->num=0;
    kref_init(&data->refcount);
    kref_get(&data->refcount);
    task=kthread_run(more_data_handling, data, "more_data_handling");
    if(task==ERR_PTR(-ENOMEM))
    {
        rv=-ENOMEM;
        goto out;
    }
    data->num++;
 out:
    kref_put(&data->refcount, data_release);
    printk(KERN_EMERG "End of my_data_handler %d\n", data->num);
    return rv;
}

static int __init try_kref_1_init(void)
{
	printk(KERN_EMERG "try_kref_1_init\n");
        my_data_handler();
	return 0;
}

static void __exit try_kref_1_exit(void)
{
	printk(KERN_EMERG "try_kref_1_exit\n");
	return;
}

module_init(try_kref_1_init);
module_exit(try_kref_1_exit);
