#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
	printk(KERN_INFO "testing.\n");
	return 5;
}
void cleanup_module(void)
{
	printk(KERN_INFO "done tes.\n");

}