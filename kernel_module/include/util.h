#ifndef __KSU_H_UTIL
#define __KSU_H_UTIL

#include "linux/fdtable.h" // IWYU pragma: keep
#include <linux/version.h>
#include <linux/syscalls.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/cred.h>
#include <linux/ptrace.h>

#include "arch.h"

#if defined(__aarch64__)
/* S15: __arm64_sys_* wrappers are NOT exported by the vivo kernel.
 * KSU_SYS_PREFIX(name) resolves to a function pointer fetched from the
 * sys_call_table via the hardcoded table offset (see infra/s15_addr.h). */
#include "../infra/s15_addr.h"
#define KSU_SYS_PREFIX(name)                                                                           \
    ((long (*)(const struct pt_regs *))ksu_s15_syscall_fn(KSU_S15_SYS_NR_##name))
#elif defined(__x86_64__)
#define KSU_SYS_PREFIX(name) __x64_sys_##name
#elif defined(__riscv)
#define KSU_SYS_PREFIX(name) __riscv_sys_##name
#else // wire up your arch here.
static_assert(1 == 0, "Unsupported architecture!");
#define KSU_SYS_PREFIX(name) sys_##name
#endif

/**
 * ksyscall: call syscalls from kernelspace
 * - tries to copy unistd's syscall()
 *
 * usage: ksyscall(close, fd);
 */
#define __ksyscall(name, a, b, c, d, e, f)                                                                             \
    ({                                                                                                                 \
        struct pt_regs __ksu_regs = { 0 };                                                                             \
        PT_REGS_SYSCALL_PARM1(&__ksu_regs) = (unsigned long)(a);                                                       \
        PT_REGS_PARM2(&__ksu_regs) = (unsigned long)(b);                                                               \
        PT_REGS_PARM3(&__ksu_regs) = (unsigned long)(c);                                                               \
        PT_REGS_SYSCALL_PARM4(&__ksu_regs) = (unsigned long)(d);                                                       \
        PT_REGS_PARM5(&__ksu_regs) = (unsigned long)(e);                                                               \
        PT_REGS_PARM6(&__ksu_regs) = (unsigned long)(f);                                                               \
        (long)KSU_SYS_PREFIX(name)(&__ksu_regs);                                                                       \
    })

// https://elixir.bootlin.com/musl/v1.2.6/source/src/internal/syscall.h#L45
#define ksyscall_0(name) __ksyscall(name, 0, 0, 0, 0, 0, 0)
#define ksyscall_1(name, a) __ksyscall(name, a, 0, 0, 0, 0, 0)
#define ksyscall_2(name, a, b) __ksyscall(name, a, b, 0, 0, 0, 0)
#define ksyscall_3(name, a, b, c) __ksyscall(name, a, b, c, 0, 0, 0)
#define ksyscall_4(name, a, b, c, d) __ksyscall(name, a, b, c, d, 0, 0)
#define ksyscall_5(name, a, b, c, d, e) __ksyscall(name, a, b, c, d, e, 0)
#define ksyscall_6(name, a, b, c, d, e, f) __ksyscall(name, a, b, c, d, e, f)

#define __ksyscall_arg_n(_1, _2, _3, _4, _5, _6, _7, N, ...) N
#define __ksyscall_count_args(...) __ksyscall_arg_n(__VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)
#define __ksyscall_concat(a, b) a##b
#define __ksyscall_exp(func, arg) __ksyscall_concat(func, arg)
#define ksyscall(...) __ksyscall_exp(ksyscall_, __ksyscall_count_args(__VA_ARGS__))(__VA_ARGS__)

#define ksu_close_fd(fd) ({ ksyscall(close, fd); })
#define ksu_sys_setns(fd, flags) ({ ksyscall(setns, fd, flags); })

static inline struct file *ksu_filp_open_nonotify(const char *path, int flags)
{
    /* S15: kern_path/dentry_open/path_put are not exported; filp_open is. */
    return filp_open(path, flags | __FMODE_NONOTIFY, current_cred());
}

#endif
