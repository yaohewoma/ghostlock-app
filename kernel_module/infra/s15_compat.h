/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __KSU_S15_COMPAT_H
#define __KSU_S15_COMPAT_H
/*
 * S15 = 4.19: *_nofault APIs are 5.9+; probe_kernel_* / strncpy_from_unsafe_user
 * equivalents exist in the kernel but are NOT exported by the vivo build —
 * resolve them through the hardcoded table (infra/s15_addr.h) as pointers.
 */
#include <linux/uaccess.h>
#include "s15_addr.h"

static inline long ksu_s15_probe_kernel_read(void *dst, const void *src, size_t size)
{
    static long (*fn)(void *, const void *, size_t);
    if (!fn)
        fn = (long (*)(void *, const void *, size_t))s15_runtime_addr("probe_kernel_read");
    return fn ? fn(dst, src, size) : -EFAULT;
}

static inline long ksu_s15_probe_kernel_write(void *dst, const void *src, size_t size)
{
    static long (*fn)(void *, const void *, size_t);
    if (!fn)
        fn = (long (*)(void *, const void *, size_t))s15_runtime_addr("probe_kernel_write");
    return fn ? fn(dst, src, size) : -EFAULT;
}

static inline long ksu_s15_strncpy_from_unsafe_user(void *dst, const void __user *src, long count)
{
    static long (*fn)(void *, const void __user *, long);
    if (!fn)
        fn = (long (*)(void *, const void __user *, long))s15_runtime_addr("strncpy_from_unsafe_user");
    return fn ? fn(dst, src, count) : -EFAULT;
}

#ifndef copy_from_user_nofault
#define copy_from_user_nofault(dst, src, size) ksu_s15_probe_kernel_read(dst, src, size)
#endif
#ifndef copy_to_user_nofault
#define copy_to_user_nofault(dst, src, size) ksu_s15_probe_kernel_write(dst, src, size)
#endif
#ifndef strncpy_from_user_nofault
#define strncpy_from_user_nofault(dst, src, count) ksu_s15_strncpy_from_unsafe_user(dst, src, count)
#endif

/* ---- file / path / fd / pid shims (unexported on vivo, hardcoded table) ---- */
#include <linux/fs.h>
#include <linux/dcache.h>
#include <linux/namei.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/pid.h>
#include <linux/sched/task.h>
#include <linux/anon_inodes.h>

/* 4.19 kernel_read/write wrap vfs_read/write with set_fs(KERNEL_DS);
 * set_fs is static inline on arm64, vfs_read/vfs_write are exported. */
static inline ssize_t ksu_s15_kernel_read(struct file *f, void *buf, size_t count, loff_t *pos)
{
    ssize_t ret;
    mm_segment_t old = get_fs();
    set_fs(KERNEL_DS);
    ret = vfs_read(f, (char __user *)(uintptr_t)buf, count, pos);
    set_fs(old);
    return ret;
}
static inline ssize_t ksu_s15_kernel_write(struct file *f, const void *buf, size_t count, loff_t *pos)
{
    ssize_t ret;
    mm_segment_t old = get_fs();
    set_fs(KERNEL_DS);
    ret = vfs_write(f, (const char __user *)(uintptr_t)buf, count, pos);
    set_fs(old);
    return ret;
}
#define kernel_read(f, b, c, p) ksu_s15_kernel_read(f, b, c, p)
#define kernel_write(f, b, c, p) ksu_s15_kernel_write(f, b, c, p)

#define KSU_S15_TABLE_FN1(ret, name, atype, aval)                                                    \
    static inline ret ksu_s15_##name(atype aval)                                                     \
    {                                                                                                \
        static ret (*fn)(atype);                                                                     \
        if (!fn)                                                                                     \
            fn = (ret (*)(atype))s15_runtime_addr(#name);                                            \
        return fn ? fn(aval) : (ret)0;                                                               \
    }

#define KSU_S15_TABLE_FN2(ret, name, atype1, aval1, atype2, aval2)                                   \
    static inline ret ksu_s15_##name(atype1 aval1, atype2 aval2)                                     \
    {                                                                                                \
        static ret (*fn)(atype1, atype2);                                                            \
        if (!fn)                                                                                     \
            fn = (ret (*)(atype1, atype2))s15_runtime_addr(#name);                                   \
        return fn ? fn(aval1, aval2) : (ret)0;                                                       \
    }

#define KSU_S15_TABLE_FN3(ret, name, atype1, aval1, atype2, aval2, atype3, aval3)                    \
    static inline ret ksu_s15_##name(atype1 aval1, atype2 aval2, atype3 aval3)                       \
    {                                                                                                \
        static ret (*fn)(atype1, atype2, atype3);                                                    \
        if (!fn)                                                                                     \
            fn = (ret (*)(atype1, atype2, atype3))s15_runtime_addr(#name);                           \
        return fn ? fn(aval1, aval2, aval3) : (ret)0;                                                \
    }

/* int kern_path(const char *, unsigned, struct path *) */
KSU_S15_TABLE_FN3(int, kern_path, const char *, n1, unsigned, f1, struct path *, p1)
#define kern_path(n, f, p) ksu_s15_kern_path(n, f, p)
/* void path_put(struct path *) */
KSU_S15_TABLE_FN1(void, path_put, struct path *, p)
#define path_put(p) ksu_s15_path_put(p)
/* void path_get(struct path *) */
KSU_S15_TABLE_FN1(void, path_get, struct path *, p)
#define path_get(p) ksu_s15_path_get(p)
/* char *d_path(const struct path *, char *, int) */
static inline char *ksu_s15_d_path(const struct path *p, char *buf, int buflen)
{
    static char *(*fn)(const struct path *, char *, int);
    if (!fn)
        fn = (char *(*)(const struct path *, char *, int))s15_runtime_addr("d_path");
    return fn ? fn(p, buf, buflen) : (char *)-ENOENT;
}
#define d_path(p, b, l) ksu_s15_d_path(p, b, l)
/* void fd_install(unsigned int, struct file *) */
KSU_S15_TABLE_FN2(void, fd_install, unsigned int, fd, struct file *, file)
#define fd_install(fd, f) ksu_s15_fd_install(fd, f)
/* int get_unused_fd_flags(unsigned) */
KSU_S15_TABLE_FN1(int, get_unused_fd_flags, unsigned, fl)
#define get_unused_fd_flags(fl) ksu_s15_get_unused_fd_flags(fl)
/* void put_unused_fd(unsigned) */
KSU_S15_TABLE_FN1(void, put_unused_fd, unsigned, fd)
#define put_unused_fd(fd) ksu_s15_put_unused_fd(fd)
/* struct task_struct *get_pid_task(struct pid *, enum pid_type) */
static inline struct task_struct *ksu_s15_get_pid_task(struct pid *pid, enum pid_type type)
{
    static struct task_struct *(*fn)(struct pid *, enum pid_type);
    if (!fn)
        fn = (struct task_struct *(*)(struct pid *, enum pid_type))s15_runtime_addr("get_pid_task");
    return fn ? fn(pid, type) : NULL;
}
#define get_pid_task(p, t) ksu_s15_get_pid_task(p, t)
/* struct pid *find_vpid(int) */
static inline struct pid *ksu_s15_find_vpid(int nr)
{
    static struct pid *(*fn)(int);
    if (!fn)
        fn = (struct pid *(*)(int))s15_runtime_addr("find_vpid");
    return fn ? fn(nr) : NULL;
}
#define find_vpid(nr) ksu_s15_find_vpid(nr)
/* void put_task_struct(struct task_struct *) → __put_task_struct */
static inline void ksu_s15_put_task_struct(struct task_struct *t)
{
    static void (*fn)(struct task_struct *);
    if (!fn)
        fn = (void (*)(struct task_struct *))s15_runtime_addr("__put_task_struct");
    if (fn)
        fn(t);
}
#define put_task_struct(t) ksu_s15_put_task_struct(t)
/* int task_work_add(struct task_struct *, struct callback_head *, bool notify)
 * 4.19 has no TWA_* mode constants — discard the third argument.
 * NOTE: linux/task_work.h must be included BEFORE this macro so that the
 * real declaration is parsed unexpanded. */
#include <linux/task_work.h>
static inline int ksu_s15_task_work_add(struct task_struct *t, struct callback_head *w, int notify)
{
    static int (*fn)(struct task_struct *, struct callback_head *, int);
    if (!fn)
        fn = (int (*)(struct task_struct *, struct callback_head *, int))s15_runtime_addr("task_work_add");
    return fn ? fn(t, w, notify) : -ENOSYS;
}
#define task_work_add(t, w, ...) ksu_s15_task_work_add(t, w, 1)
/* struct file *anon_inode_getfile(const char *, const struct file_operations *, void *, int) */
static inline struct file *ksu_s15_anon_inode_getfile(const char *name,
                                                      const struct file_operations *fops,
                                                      void *priv, int flags)
{
    static struct file *(*fn)(const char *, const struct file_operations *, void *, int);
    if (!fn)
        fn = (struct file *(*)(const char *, const struct file_operations *, void *,
                               int))s15_runtime_addr("anon_inode_getfile");
    return fn ? fn(name, fops, priv, flags) : ERR_PTR(-ENOSYS);
}
#define anon_inode_getfile(n, fo, pv, fl) ksu_s15_anon_inode_getfile(n, fo, pv, fl)

/* 4.19: seccomp_filter_release does not exist; put_seccomp_filter(tsk)
 * drops the filter ref held by the fake task (same intent). */
static inline void ksu_s15_put_seccomp_filter(struct task_struct *t)
{
    static void (*fn)(struct task_struct *);
    if (!fn)
        fn = (void (*)(struct task_struct *))s15_runtime_addr("put_seccomp_filter");
    if (fn)
        fn(t);
}
#define seccomp_filter_release(t) ksu_s15_put_seccomp_filter(t)

/* 4.19: strscpy_pad is a 5.x API; zero-then-strlcpy is equivalent for
 * the fixed-size path buffers KSU uses. */
#define strscpy_pad(dst, src, count)                                                                    \
    ({                                                                                                  \
        memset((dst), 0, (count));                                                                      \
        strlcpy((dst), (src), (count));                                                                 \
    })

#endif
