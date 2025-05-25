#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

extern void exported_function(void);  /* Declare the external symbol */

static int __init mod_b_init(void) {
    printk(KERN_INFO "mod_b: Init - calling exported function from mod_a\n");
    exported_function();  /* Call function from mod_a */
    return 0;
}

static void __exit mod_b_exit(void) {
    printk(KERN_INFO "mod_b: Exit\n");
}

module_init(mod_b_init);
module_exit(mod_b_exit);

