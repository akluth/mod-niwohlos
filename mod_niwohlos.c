#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static int niwohlos_init(void) {
    printk(KERN_ALERT "niwohlos sagt Hallo!");
    return 0;
}

static int niwohlos_exit(void) {
    printk(KERN_ALERT "niwohlos sagt Tschuesskes!");
    return 0;
}

module_init(niwohlos_init);
module_exit(niwohlos_exit);
