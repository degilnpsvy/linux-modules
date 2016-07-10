#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timekeeping.h>

MODULE_LICENSE("GPL");

static int __init time_init(void)
{
    static struct timeval curr_time;
    printk(KERN_EMERG "time_init\n");
    do_gettimeofday(&curr_time);
    printk(KERN_EMERG "TIME: %d\n",cpu_to_le32(curr_time.tv_sec));
    return 0;
}
static void __exit time_exit(void)
{
    printk(KERN_EMERG "time_exit\n");
    return;
}

module_init(time_init);
module_exit(time_exit);
