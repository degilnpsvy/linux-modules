#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

MODULE_LICENSE("GPL");

static int foo, bar, baz;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", foo);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr, char *buf, size_t count)
{
    int ret;
    ret=kstrtoint(buf,10,&foo);
    if(ret<0) return ret;

    return count;
}

static struct kobj_attribute foo_attribute=__ATTR(foo, 0664, foo_show, foo_store);

static ssize_t b_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int var;
    if(strcmp(attr->attr.name, "baz")==0)
        var=baz;
    else var=bar;
    return sprintf(buf,"%d\n", var);
}

static ssize_t b_store(struct kobject *kobj, struct kobj_attribute *attr, char *buf, size_t count)
{
    int var,ret;

    ret=kstrtoint(buf,10,&var);
    if(ret<0) return ret;

    if(strcmp(attr->attr.name , "baz")==0)
        baz=var;
    else
        bar=var;
    return count;
}

static struct kobj_attribute baz_attribute=__ATTR(baz, 0664, b_show, b_store);
static struct kobj_attribute bar_attribute=__ATTR(bar, 0664, b_show, b_store);

static struct attribute *attrs[]= {
    &foo_attribute.attr,
    &baz_attribute.attr,
    &bar_attribute.attr,
    NULL,
};

static struct attribute_group attr_group= {
    .attrs=attrs,
};

static struct kobject *example_kobj;

static int __init example_kobj_init(void)
{
    printk(KERN_EMERG "example_kobj_init\n");

    int retval;
    example_kobj=kobject_create_and_add("kobject_example", kernel_kobj);
    if (!example_kobj) return -ENOMEM;

    retval=sysfs_create_group(example_kobj, &attr_group);
    if(retval)
        kobject_put(example_kobj);

    return retval;
}

static void __exit example_kobj_exit(void)
{
    printk(KERN_EMERG "example_kobj_exit\n");
    kobject_put(example_kobj);
    return;
}

module_init(example_kobj_init);
module_exit(example_kobj_exit);
