/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __KSU_S15_SHIM_H
#define __KSU_S15_SHIM_H

/*
 * S15 (vivo PD2203, 4.19.152-perf+): symbols below are present in the kernel
 * but NOT exported, and stripped from kallsyms. Calls must go through the
 * hardcoded table (infra/s15_addr.c) as function pointers. Include this header
 * AFTER the linux headers that declare these functions.
 */
#include "s15_addr.h"

/* ---- cred family ---- */
static inline int ksu_s15_commit_creds(struct cred *new)
{
    static int (*fn)(struct cred *);
    if (!fn)
        fn = (int (*)(struct cred *))s15_runtime_addr("commit_creds");
    return fn ? fn(new) : -1;
}
#define commit_creds(new) ksu_s15_commit_creds(new)

static inline const struct cred *ksu_s15_override_creds(const struct cred *new)
{
    static const struct cred *(*fn)(const struct cred *);
    if (!fn)
        fn = (const struct cred *(*)(const struct cred *))s15_runtime_addr("override_creds");
    return fn ? fn(new) : NULL;
}
#define override_creds(new) ksu_s15_override_creds(new)

static inline void ksu_s15_revert_creds(const struct cred *old)
{
    static void (*fn)(const struct cred *);
    if (!fn)
        fn = (void (*)(const struct cred *))s15_runtime_addr("revert_creds");
    if (fn)
        fn(old);
}
#define revert_creds(old) ksu_s15_revert_creds(old)

static inline struct cred *ksu_s15_prepare_kernel_cred(struct task_struct *t)
{
    static struct cred *(*fn)(struct task_struct *);
    if (!fn)
        fn = (struct cred *(*)(struct task_struct *))s15_runtime_addr("prepare_kernel_cred");
    return fn ? fn(t) : NULL;
}
#define prepare_kernel_cred(t) ksu_s15_prepare_kernel_cred(t)

/* ---- task family ---- */
static inline struct task_struct *ksu_s15_find_task_by_vpid(pid_t nr)
{
    static struct task_struct *(*fn)(pid_t);
    if (!fn)
        fn = (struct task_struct *(*)(pid_t))s15_runtime_addr("find_task_by_vpid");
    return fn ? fn(nr) : NULL;
}
#define find_task_by_vpid(nr) ksu_s15_find_task_by_vpid(nr)

static inline int ksu_s15_switch_task_namespaces(struct task_struct *t, struct nsproxy *new)
{
    static int (*fn)(struct task_struct *, struct nsproxy *);
    if (!fn)
        fn = (int (*)(struct task_struct *, struct nsproxy *))s15_runtime_addr("switch_task_namespaces");
    return fn ? fn(t, new) : -1;
}
#define switch_task_namespaces(t, n) ksu_s15_switch_task_namespaces(t, n)

#endif
