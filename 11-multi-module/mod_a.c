/*
	"We’ve seen how insmodresolves undefined symbols against the table of public ker-
	nel symbols. The table contains the addresses of global kernel items—functions and
	variables—that are needed to implement modularized drivers. When a module is
	loaded, any symbol exported by the module becomes part of the kernel symbol table.
	In the usual case, a module implements its own functionality without the need to
	export any symbols at all. You need to export symbols, however, whenever other
	modules may benefit from using them." - LDD (chaper 2)
*/

#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

void exported_function(void) {
    printk(KERN_INFO "mod_a: Exported function called!\n");
}
EXPORT_SYMBOL(exported_function);

static int __init mod_a_init(void) {
    printk(KERN_INFO "mod_a: Init\n");
    return 0;
}

static void __exit mod_a_exit(void) {
    printk(KERN_INFO "mod_a: Exit\n");
}

module_init(mod_a_init);
module_exit(mod_a_exit);

