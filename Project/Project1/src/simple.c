#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/hash.h>
#include<linux/gcd.h>
#include<linux/jiffies.h>

int simple_init(void){
    printk(KERN_INFO "Loading Module\n");
    printk(KERN_INFO "%lu\n", GOLDEN_RATIO_PRIME);
    printk(KERN_INFO "%lu\n", jiffies);
    printk(KERN_INFO "%u\n", HZ);
    return 0;
}

void simple_exit(void){
    printk(KERN_INFO "Removing Module\n");
    printk(KERN_INFO "%lu\n", gcd(3300,24));
    printk(KERN_INFO "%lu\n", jiffies);
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("LogCreative");