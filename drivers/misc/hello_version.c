#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/utsname.h>

static char *who = "unknown";
module_param(who, charp, 0444);

static struct timeval load_time;

static int __init hello_version_init(void)
{
	do_gettimeofday(&load_time);

	pr_info("Hello %s. You are currently using Linux %s\n",
		who, utsname()->release);

	return 0;
}

static void __exit hello_version_exit(void)
{
	struct timeval unload_time;
	__kernel_time_t seconds_passed;

	do_gettimeofday(&unload_time);
	seconds_passed = unload_time.tv_sec - load_time.tv_sec;
	pr_info("Goodbye %s, after %ld seconds\n", who, seconds_passed);
}

module_init(hello_version_init);
module_exit(hello_version_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Andreas' hello version module");
MODULE_AUTHOR("Andreas Kleist Svendsen");

