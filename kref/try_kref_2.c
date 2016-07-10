#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

static DEFINE_MUTEX(mutex);
static LIST_HEAD(head);
struct my_data
{
    struct kref refcount;
    struct list_head link;
};

static struct my_data * get_entry(void)
{
    struct my_data *entry=NULL;
    printk(KERN_EMERG "in get_entry\n");
    mutex_lock(&mutex);
    if(!list_empty(&head))
    {
        entry=container_of(head.next, struct my_data, link);
        kref_get(&entry->refcount);
    }
    mutex_unlock(&mutex);
    return entry;
}

/* static void release_entry(struct kref * ref) */
/* { */
/*     struct my_data *entry=container_of(ref, struct my_data, refcount); */
/*     list_del(&entry->link); */
/*     kfree(entry); */
/* } */

/* static void put_entry(struct my_data *entry) */
/* { */
/*     mutex_lock(&mutex); */
/*     kref_put(&entry->refcount, release_entry); */
/*     mutex_unlock(&mutex); */
/* } */

// Here is a better way to do release_entry and put_entry

static void release_entry(struct kref *ref)
{
}

static void put_entry(struct my_data * entry)
{
    printk(KERN_EMERG "in put_entry\n");
    mutex_lock(&mutex);
    if (kref_put(&entry->refcount, release_entry))
    {
        list_del(&entry->link);
        mutex_unlock(&mutex);
        kfree(entry);
    }
    else
        mutex_unlock(&mutex);
}

static int __init try_kref_2_init(void)
{
        struct my_data *entry;
	printk(KERN_EMERG "try_kref_2_init\n");
        entry=get_entry();
        if(entry) put_entry(entry);
	return 0;
}

static void __exit try_kref_2_exit(void)
{
	printk(KERN_EMERG "try_kref_2_exit\n");
	return;
}

module_init(try_kref_2_init);
module_exit(try_kref_2_exit);
