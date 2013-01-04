#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Kluth <derhartmut@niwohlos.org>");
MODULE_DESCRIPTION("Total niwohloses Linux-Kernel-Modul.");

#define DEVICE_NAME "niwohlos"
static int major_number = 0;

static ssize_t niwohlos_read(struct file *file, char *buf, ssize_t count, loff_t *ppos) {
    char *hello_str = "Wir sind niwohlos und das ist auch gut so. #niwohlos.\n";
    int len = strlen(hello_str); /* Don't include the null byte. */

    if (count < len)
        return -EINVAL;

    if (*ppos != 0)
        return 0;

    if (copy_to_user(buf, hello_str, len))
        return -EINVAL;

    *ppos = len;

    return len;
}

/**
 * Device operations die wir fuer unser niwohloses Imperium
 * brauchen
 **/
static struct file_operations fops = {
    .read = niwohlos_read
};


static struct miscdevice niwohlos_dev = {
    MISC_DYNAMIC_MINOR,
    "niwohlos",
    &fops
};





/***
 * Initialisierung ist alles!
 *
 * Alles niwohlose nimmt hier seinen Lauf
 ***/
static int niwohlos_init(void) {
    printk(KERN_ALERT "niwohlos sagt Hallo!");

    int ret;

    ret = misc_register(&niwohlos_dev);

    if (ret) {
        printk(KERN_ERR "Wat, wir koennen keine niwohlosigkeit deinem Kernel hinzufuegen!");
    }

    return ret;
}

static int niwohlos_exit(void) {
    printk(KERN_ALERT "niwohlos sagt Tschuesskes!");

    misc_deregister(&niwohlos_dev);
    return 0;
}

module_init(niwohlos_init);
module_exit(niwohlos_exit);
