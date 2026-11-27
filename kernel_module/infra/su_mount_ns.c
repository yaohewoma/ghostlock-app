// SPDX-License-Identifier: GPL-2.0
/*
 * S15 port: mount-namespace switching is DISABLED.
 *
 * Upstream implementation needs kern_path / dentry_open / d_path /
 * get_fs_pwd / set_fs_pwd / get_fs_root / path_mount / ksys_unshare /
 * ns_get_path / find_pid_ns — none of them are exported by the vivo
 * 4.19 kernel (verified against the 1166-symbol Module.symvers).
 * su sessions therefore run in the inherited namespace; no functional
 * impact on root itself.
 */
#include <linux/sched.h>

#include "klog.h" // IWYU pragma: keep
#include "infra/su_mount_ns.h"

void setup_mount_ns(int32_t ns_mode)
{
    if (ns_mode != KSU_NS_INHERITED)
        pr_info("s15: mount ns mode %d not supported, running inherited\n", ns_mode);
}
