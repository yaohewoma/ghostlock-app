/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __KSU_S15_ADDR_H
#define __KSU_S15_ADDR_H

#include <linux/types.h>

extern unsigned long ksu_s15_kbase;

unsigned long s15_lookup_link_offset(const char *name);
unsigned long s15_runtime_addr(const char *name);
void ksu_s15_glue_init(void);

/*
 * S15 native sys_call_table link offset (RELA scan, T1 base; entries are
 * function pointers to __arm64_sys_* wrappers, 8 bytes each).
 */
#define KSU_S15_SYSCALL_TABLE_OFFSET 0x17808a8UL

/* syscall numbers needed by ksyscall() users (asm-generic unistd) */
#define KSU_S15_SYS_NR_close 57
#define KSU_S15_SYS_NR_mount 40
#define KSU_S15_SYS_NR_setns 268
#define KSU_S15_SYS_NR_unshare 272

/* Resolve syscall wrapper fn through sys_call_table — no exported symbol needed */
static inline void *ksu_s15_syscall_fn(unsigned int nr)
{
    unsigned long *slot =
        (unsigned long *)(ksu_s15_kbase + KSU_S15_SYSCALL_TABLE_OFFSET +
                          (unsigned long)nr * 8);
    return (void *)(*slot);
}

/* helper: verify kbase sanity — _text maps to a kernel VA */
static inline int s15_kbase_valid(void)
{
#ifdef __aarch64__
    return (ksu_s15_kbase & 0xffffffffUL) == 0x80800000UL && (ksu_s15_kbase >> 32) == 0xffffff80UL;
#else
    return ksu_s15_kbase != 0;
#endif
}

#endif
