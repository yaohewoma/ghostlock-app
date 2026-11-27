// SPDX-License-Identifier: GPL-2.0
/*
 * S15 (vivo PD2203, 4.19.152-perf+) symbol resolver.
 *
 * Replaces the upstream resolver: vivo strips sensitive symbols from kallsyms
 * and does not export kallsyms_lookup_name. All critical symbols come from a
 * hardcoded link-offset table (see infra/s15_addr.c), with runtime
 * kallsyms_lookup_name as fallback for symbols vivo kept.
 */
#include <linux/kallsyms.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/version.h>

#include "infra/symbol_resolver.h"
#include "infra/s15_addr.h"

unsigned long find_kernel_symbol_exact(const char *symbol_name)
{
    if (!symbol_name || !symbol_name[0])
        return 0;

    if (!s15_kbase_valid()) {
        pr_err("ksu_s15: kbase not set or invalid (0x%lx) — insmod with kbase=<runtime _text VA>\n",
               ksu_s15_kbase);
        return 0;
    }

    return s15_runtime_addr(symbol_name);
}

void *ksu_resolve_symbol_for_functable_hook(const char *symbol_name)
{
    /* 4.19 vivo kernel: no CFI, no .cfi_jt trampolines — direct lookup */
    return (void *)find_kernel_symbol_exact(symbol_name);
}

void __init ksu_init_symbol_resolver()
{
    pr_info("ksu_s15: resolver ready, kbase=0x%lx\n", ksu_s15_kbase);
    if (!s15_kbase_valid())
        pr_warn("ksu_s15: kbase unset — load with: insmod ksu_raw.ko kbase=0x<runtime _text VA>\n");
}
