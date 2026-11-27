/* GENERATED — pointer table initializer for s15_glue_asm.S */
#include <linux/compiler.h>
#include <linux/kernel.h>
#include <linux/lsm_hooks.h>
#include <linux/printk.h>
#include <linux/types.h>
#include "s15_addr.h"

extern unsigned long s15_glue_ptr___get_task_comm;
extern unsigned long s15_glue_ptr___put_cred;
extern unsigned long s15_glue_ptr___task_pid_nr_ns;
extern unsigned long s15_glue_ptr__copy_to_iter;
extern unsigned long s15_glue_ptr__raw_read_lock;
extern unsigned long s15_glue_ptr__raw_read_unlock;
extern unsigned long s15_glue_ptr__raw_spin_lock_irq;
extern unsigned long s15_glue_ptr__raw_spin_unlock_irq;
extern unsigned long s15_glue_ptr_abort_creds;
extern unsigned long s15_glue_ptr_alloc_anon_inode;
extern unsigned long s15_glue_ptr_alloc_file_pseudo;
extern unsigned long s15_glue_ptr_alloc_uid;
extern unsigned long s15_glue_ptr_bin2hex;
extern unsigned long s15_glue_ptr_crypto_shash_digest;
extern unsigned long s15_glue_ptr_dentry_open;
extern unsigned long s15_glue_ptr_down_read;
extern unsigned long s15_glue_ptr_ext4_unregister_sysfs;
extern unsigned long s15_glue_ptr_fget;
extern unsigned long s15_glue_ptr_fortify_panic;
extern unsigned long s15_glue_ptr_free_uid;
extern unsigned long s15_glue_ptr_fsnotify_add_mark;
extern unsigned long s15_glue_ptr_fsnotify_alloc_group;
extern unsigned long s15_glue_ptr_fsnotify_destroy_mark;
extern unsigned long s15_glue_ptr_fsnotify_init_mark;
extern unsigned long s15_glue_ptr_fsnotify_put_group;
extern unsigned long s15_glue_ptr_fsnotify_put_mark;
extern unsigned long s15_glue_ptr_generic_file_llseek;
extern unsigned long s15_glue_ptr_get_task_cred;
extern unsigned long s15_glue_ptr_groups_alloc;
extern unsigned long s15_glue_ptr_groups_free;
extern unsigned long s15_glue_ptr_groups_sort;
extern unsigned long s15_glue_ptr_ihold;
extern unsigned long s15_glue_ptr_iput;
extern unsigned long s15_glue_ptr_iterate_dir;
extern unsigned long s15_glue_ptr_kallsyms_lookup_size_offset;
extern unsigned long s15_glue_ptr_kasprintf;
extern unsigned long s15_glue_ptr_kern_path;
extern unsigned long s15_glue_ptr_kfree_call_rcu;
extern unsigned long s15_glue_ptr_kick_all_cpus_sync;
extern unsigned long s15_glue_ptr_kvfree;
extern unsigned long s15_glue_ptr_kvmalloc_node;
extern unsigned long s15_glue_ptr_memchr;
extern unsigned long s15_glue_ptr_noop_llseek;
extern unsigned long s15_glue_ptr_path_put;
extern unsigned long s15_glue_ptr_prepare_creds;
extern unsigned long s15_glue_ptr_refcount_dec_and_test_checked;
extern unsigned long s15_glue_ptr_refcount_inc_not_zero_checked;
extern unsigned long s15_glue_ptr_security_release_secctx;
extern unsigned long s15_glue_ptr_security_secctx_to_secid;
extern unsigned long s15_glue_ptr_security_secid_to_secctx;
extern unsigned long s15_glue_ptr_set_groups;
extern unsigned long s15_glue_ptr_strscpy;
extern unsigned long s15_glue_ptr_synchronize_rcu;
extern unsigned long s15_glue_ptr_synchronize_sched;
extern unsigned long s15_glue_ptr_synchronize_srcu;
extern unsigned long s15_glue_ptr_tracepoint_probe_register_prio;
extern unsigned long s15_glue_ptr_tracepoint_probe_unregister;

struct s15_glue_ent { const char *name; unsigned long *ptr; };
static const struct s15_glue_ent s15_glue_table[] = {
    { "__get_task_comm", &s15_glue_ptr___get_task_comm },
    { "__put_cred", &s15_glue_ptr___put_cred },
    { "__task_pid_nr_ns", &s15_glue_ptr___task_pid_nr_ns },
    { "_copy_to_iter", &s15_glue_ptr__copy_to_iter },
    { "_raw_read_lock", &s15_glue_ptr__raw_read_lock },
    { "_raw_read_unlock", &s15_glue_ptr__raw_read_unlock },
    { "_raw_spin_lock_irq", &s15_glue_ptr__raw_spin_lock_irq },
    { "_raw_spin_unlock_irq", &s15_glue_ptr__raw_spin_unlock_irq },
    { "abort_creds", &s15_glue_ptr_abort_creds },
    { "alloc_anon_inode", &s15_glue_ptr_alloc_anon_inode },
    { "alloc_file_pseudo", &s15_glue_ptr_alloc_file_pseudo },
    { "alloc_uid", &s15_glue_ptr_alloc_uid },
    { "bin2hex", &s15_glue_ptr_bin2hex },
    { "crypto_shash_digest", &s15_glue_ptr_crypto_shash_digest },
    { "dentry_open", &s15_glue_ptr_dentry_open },
    { "down_read", &s15_glue_ptr_down_read },
    { "ext4_unregister_sysfs", &s15_glue_ptr_ext4_unregister_sysfs },
    { "fget", &s15_glue_ptr_fget },
    { "fortify_panic", &s15_glue_ptr_fortify_panic },
    { "free_uid", &s15_glue_ptr_free_uid },
    { "fsnotify_add_mark", &s15_glue_ptr_fsnotify_add_mark },
    { "fsnotify_alloc_group", &s15_glue_ptr_fsnotify_alloc_group },
    { "fsnotify_destroy_mark", &s15_glue_ptr_fsnotify_destroy_mark },
    { "fsnotify_init_mark", &s15_glue_ptr_fsnotify_init_mark },
    { "fsnotify_put_group", &s15_glue_ptr_fsnotify_put_group },
    { "fsnotify_put_mark", &s15_glue_ptr_fsnotify_put_mark },
    { "generic_file_llseek", &s15_glue_ptr_generic_file_llseek },
    { "get_task_cred", &s15_glue_ptr_get_task_cred },
    { "groups_alloc", &s15_glue_ptr_groups_alloc },
    { "groups_free", &s15_glue_ptr_groups_free },
    { "groups_sort", &s15_glue_ptr_groups_sort },
    { "ihold", &s15_glue_ptr_ihold },
    { "iput", &s15_glue_ptr_iput },
    { "iterate_dir", &s15_glue_ptr_iterate_dir },
    { "kallsyms_lookup_size_offset", &s15_glue_ptr_kallsyms_lookup_size_offset },
    { "kasprintf", &s15_glue_ptr_kasprintf },
    { "kern_path", &s15_glue_ptr_kern_path },
    { "kfree_call_rcu", &s15_glue_ptr_kfree_call_rcu },
    { "kick_all_cpus_sync", &s15_glue_ptr_kick_all_cpus_sync },
    { "kvfree", &s15_glue_ptr_kvfree },
    { "kvmalloc_node", &s15_glue_ptr_kvmalloc_node },
    { "memchr", &s15_glue_ptr_memchr },
    { "noop_llseek", &s15_glue_ptr_noop_llseek },
    { "path_put", &s15_glue_ptr_path_put },
    { "prepare_creds", &s15_glue_ptr_prepare_creds },
    { "refcount_dec_and_test_checked", &s15_glue_ptr_refcount_dec_and_test_checked },
    { "refcount_inc_not_zero_checked", &s15_glue_ptr_refcount_inc_not_zero_checked },
    { "security_release_secctx", &s15_glue_ptr_security_release_secctx },
    { "security_secctx_to_secid", &s15_glue_ptr_security_secctx_to_secid },
    { "security_secid_to_secctx", &s15_glue_ptr_security_secid_to_secctx },
    { "set_groups", &s15_glue_ptr_set_groups },
    { "strscpy", &s15_glue_ptr_strscpy },
    { "synchronize_rcu", &s15_glue_ptr_synchronize_rcu },
    { "synchronize_sched", &s15_glue_ptr_synchronize_sched },
    { "synchronize_srcu", &s15_glue_ptr_synchronize_srcu },
    { "tracepoint_probe_register_prio", &s15_glue_ptr_tracepoint_probe_register_prio },
    { "tracepoint_probe_unregister", &s15_glue_ptr_tracepoint_probe_unregister },
};

void __init ksu_s15_glue_init(void)
{
    unsigned long addr;
    int i;
    for (i = 0; i < ARRAY_SIZE(s15_glue_table); i++) {
        addr = s15_runtime_addr(s15_glue_table[i].name);
        *s15_glue_table[i].ptr = addr;
        if (!addr)
            pr_warn("s15 glue: %s unresolved\n", s15_glue_table[i].name);
    }
}

/* Only used by STATIC_KEY_CHECK_USE WARN(); a local true value is correct. */
bool static_key_initialized = true;

/* selinux_blob_sizes is stripped from device kallsyms; SELinux owns the
 * first cred/inode blob slots on this build (offset 0). A local zeroed
 * definition satisfies objsec.h inlines in file_wrapper.c. */
struct lsm_blob_sizes selinux_blob_sizes;

/* vivo inlined __rcu_read_lock: nesting++ + barrier. task_struct offset
 * 0x4d0 confirmed by disassembly of inlined callers in the device image. */
void __rcu_read_lock(void)
{
    void *t;
    volatile int *nesting;
    asm volatile("mrs %0, sp_el0" : "=r"(t));
    nesting = (volatile int *)((char *)t + 0x4d0);
    *nesting = *nesting + 1;
    barrier();
}

