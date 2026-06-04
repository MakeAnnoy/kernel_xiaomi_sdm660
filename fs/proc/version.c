// SPDX-License-Identifier: GPL-2.0
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/utsname.h>

/* Limitless Identity */
#ifdef CONFIG_LIMITLESS
extern char thre_user_name[];
extern char thre_host_name[];
extern char thre_compiler[];
#endif

static int version_proc_show(struct seq_file *m, void *v)
{
#ifdef CONFIG_LIMITLESS
	seq_printf(m, linux_proc_banner,
		utsname()->sysname,
		utsname()->release,
		thre_user_name,
		thre_host_name,
		thre_compiler,
		utsname()->version);
#else
	seq_printf(m, linux_proc_banner,
		utsname()->sysname,
		utsname()->release,
		utsname()->version);
#endif
	return 0;
}

static int __init proc_version_init(void)
{
	proc_create_single("version", 0, NULL, version_proc_show);
	return 0;
}
fs_initcall(proc_version_init);
