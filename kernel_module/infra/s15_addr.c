// SPDX-License-Identifier: GPL-2.0
/*
 * OPPO K7x (PERM00), 4.14.186+ hardcoded symbol resolver.
 * Generated 2026-11-27 from device kallsyms (56,187 syms) + RELA.dyn exact method.
 * Offsets are VA - _text(0xffffff8008080000).
 * EXACT = RELA/disasm verified; kallsyms = from device kallsyms;
 * TODO = data symbol stripped by KALLSYMS_ALL=n, needs RELA derivation.
 */
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/string.h>

#include "s15_addr.h"

unsigned long ksu_s15_kbase;
module_param_named(kbase, ksu_s15_kbase, ulong, 0400);
MODULE_PARM_DESC(kbase, "runtime VA of kernel _text");

struct s15_sym { const char *name; unsigned long off; };

static const struct s15_sym s15_table[] = {
    { "commit_creds", 0x00063700 },
    { "prepare_kernel_cred", 0x00063A9C },
    { "override_creds", 0x000639D4 },
    { "init_task", 0x0201D0C0 },
    { "init_cred", 0x0202A9E8 },
    { "init_nsproxy", 0x0202A870 },  /* RELA: init_task+0x818 */
    { "sys_call_table", 0x010E2000 },  /* RELA run: 435 sys_* ptrs, io_setup..pidfd_open */
    { "compat_sys_call_table", 0x01632130 },  /* RELA run: 77 sys_vm86old slots */
    { "__arm64_sys_ni_syscall", 0x000619A4 },  /* 4.14 alias: sys_ni_syscall */
    { "sys_ni_syscall", 0x000619A4 },
    { "kallsyms_lookup_name", 0x00104D10 },
    { "selinux_state", 0x0A0F2710 },
    { "selinux_enforcing", 0x0A0F2710 },
    { "stop_machine", 0x0011B5DC },
    { "probe_kernel_write", 0x00192954 },
    { "probe_kernel_read", 0x00192868 },
    { "__flush_dcache_area", 0x00023C84 },
    { "__flush_icache_range", 0x00023BB4 },  /* alias: flush_icache_range (4.14) */
    { "module_blacklist", 0x00000000 },  /* 4.14: no native symbol, runtime lookup warns only */
    { "security_hook_heads", 0x0A52CB10 },
    { "find_task_by_vpid", 0x0005DA78 },
    { "switch_task_namespaces", 0x00061DA0 },
    { "init_uts_ns", 0x0201C278 },  /* RELA: init_nsproxy+8 (uts_ns field) */
    { "context_struct_compute_av", 0x003FCC6C },
    { "sel_handle_status_ops", 0x00000000 },  /* 4.14: 5.x-only mechanism, absent */
    { "kern_path", 0x0021AB34 },
    { "path_put", 0x0021A2BC },
    { "path_get", 0x0021A280 },
    { "d_path", 0x0022FFC4 },
    { "dentry_path_raw", 0x002302AC },
    { "fd_install", 0x002361EC },
    { "get_unused_fd_flags", 0x00235FB8 },
    { "put_unused_fd", 0x00235FF0 },
    { "__close_fd", 0x0023621C },
    { "get_pid_task", 0x0005DBA0 },
    { "__put_task_struct", 0x0002F44C },
    { "find_vpid", 0x0005D72C },
    { "task_work_add", 0x0005E0D4 },
    { "anon_inode_getfile", 0x00269F48 },
    { "strncpy_from_unsafe_user", 0x00192A40 },  /* alias: strncpy_from_unsafe (4.14) */
    { "dentry_open", 0x00208D18 },
    { "kernel_read", 0x0020A1E0 },
    { "kernel_write", 0x0020A68C },
};

unsigned long s15_lookup_link_offset(const char *name)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(s15_table); i++)
        if (strcmp(s15_table[i].name, name) == 0)
            return s15_table[i].off;
    return 0;
}

unsigned long s15_runtime_addr(const char *name)
{
    unsigned long off = s15_lookup_link_offset(name);
    if (off) return ksu_s15_kbase + off;
    if (ksu_s15_kbase) {
        static unsigned long (*lookup_fn)(const char *) = NULL;
        if (!lookup_fn)
            lookup_fn = (void *)(ksu_s15_kbase + 0x00104D10); /* kallsyms_lookup_name */
        return lookup_fn(name);
    }
    return 0;
}
