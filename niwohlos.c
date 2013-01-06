#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/random.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "niwohlos"


/***
 * Wer lesen moechte, bekommt was zum Lesen!
 ***/
static ssize_t niwohlos_read(struct file *file, char *buf, ssize_t count, loff_t *ppos) {
    char *insults[] = {
        "Wir sind niwohlos und das ist auch gut so. #niwohlos.",
        "Ficken",
        "ehenkes",
        "Hurenfick"
    };

    int random_seed;
    get_random_bytes(&random_seed, sizeof(random_seed));

    random_seed = random_seed % 3;

    int len = strlen(insults[random_seed]);

    if (count < len)
        return -EINVAL;

    if (*ppos != 0)
        return 0;

    if (copy_to_user(buf, insults[random_seed], len))
        return -EINVAL;

    *ppos = len;

    return len;
}


/***
 * Device operations die wir fuer unser niwohloses Imperium
 * brauchen
 ***/
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = niwohlos_read
};


/***
 * Das niwohlose Device unter /dev registrieren
 ***/
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
    printk(KERN_ALERT "Dein Kernel wird nun von der niwohlosigkeit ueberfallen...!");

    int ret = misc_register(&niwohlos_dev);

    if (ret) {
        printk(KERN_ERR "Wat, wir koennen keine niwohlosigkeit deinem Kernel hinzufuegen!");
    }

    return ret;
}


/***
 * Hier hat dann aber auch die niwohlosigkeit ein Ende.
 ***/
static int niwohlos_exit(void) {
    printk(KERN_ALERT "niwohlos sagt Tschuesskes!");

    misc_deregister(&niwohlos_dev);
    return 0;
}


module_init(niwohlos_init);
module_exit(niwohlos_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Kluth <derhartmut@niwohlos.org>");
MODULE_DESCRIPTION("Total niwohloses Linux-Kernel-Modul.");
