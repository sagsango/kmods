#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mydevice"
#define BUF_LEN 100

static dev_t dev_num;
static struct cdev my_cdev;
static char device_buf[BUF_LEN];

static int my_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "mychar: device opened\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "mychar: device closed\n");
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    ssize_t bytes;
    bytes = simple_read_from_buffer(buf, len, offset, device_buf, BUF_LEN);
    printk(KERN_INFO "mychar: read %zd bytes\n", bytes);
    return bytes;
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    ssize_t bytes;
    bytes = simple_write_to_buffer(device_buf, BUF_LEN, offset, buf, len);
    printk(KERN_INFO "mychar: wrote %zd bytes\n", bytes);
    return bytes;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
};

static int __init my_init(void) {
    int ret;

    // Allocate device numbers
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ERR "mychar: failed to allocate device number\n");
        return ret;
    }

    // Initialize and add cdev
    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;

    ret = cdev_add(&my_cdev, dev_num, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "mychar: failed to add cdev\n");
        return ret;
    }

    printk(KERN_INFO "mychar: registered with major %d minor %d\n", MAJOR(dev_num), MINOR(dev_num));
    return 0;
}

static void __exit my_exit(void) {
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "mychar: unregistered\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple character device driver");
MODULE_VERSION("1.0");

module_init(my_init);
module_exit(my_exit);

