#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

/*the function is called when module is loading */
int hello(void)
{
	printk(KERN_INFO "Hello World ! \n");
	return 0 ;
}

/*exit the module*/
void bye(void)
{
	printk(KERN_INFO " Bye ! \n ");
	
}

module_init(hello);
module_exit(bye);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello Module");
MODULE_LICENSE("SGG");
