#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>

#include <asm/uaccess.h>

static ssize_t axo_read(struct file * file, char * buf, 
			  size_t count, loff_t *curpos)
{
	char *axo_str = "entered axo!\n";
	int len = strlen(axo_str); 

	//per evitare letture multiple da parte di cat
	//accettiamo solo letture da posizione iniziale
	if (*curpos != 0) return 0;

	if (copy_to_user(buf, axo_str, len)) return -EINVAL;

	printk(KERN_ERR "READ function entered\n");
	*curpos = len;

	return len;
}

static const struct file_operations axo_fops = {
	.owner		= THIS_MODULE,
	.read		= axo_read,
};

static struct miscdevice axo_dev = {
	
	MISC_DYNAMIC_MINOR, //minor irrelevant
	"axo",        // device /dev/axo
	&axo_fops     // file operations
};

static int __init
axo_init(void)
{
	int ret;
	ret = misc_register(&axo_dev);
	if (ret)
		printk(KERN_ERR "Unable to register \"axo\" misc device\n");
	else 
		printk(KERN_INFO "REGISTERED \"axo\" misc device\n");
	return ret;
}

module_init(axo_init);

static void __exit
axo_exit(void)
{
	misc_deregister(&axo_dev);
}

module_exit(axo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("gp");
MODULE_DESCRIPTION("\"device per creare modulo di info");
MODULE_VERSION("");
