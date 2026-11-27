# K7x ksu_raw.ko 云端构建仓库

OPPO K7x（PERM00 / MT6853 / Dimensity 720，4.14.186+）的 KernelSU LKM 构建工程。

## 为什么在云端编

本机 Windows 无法编译内核模块：
- GNU make（ezwinports）的 `$(CURDIR)` 带盘符冒号 `C:/...`，内核 Makefile:128 直接拒绝。
- WSL 被安全策略拦截，无 MSYS make / `aarch64-linux-gnu-gcc`。

GitHub Actions `ubuntu-22.04` 无此限制。

## 素材来源（全部逆向自 K7x 官方 F.20 OTA）

| 文件 | 来源 |
|---|---|
| `config/k7x_defconfig` | 官方 boot.img 内嵌 config（5762 行） |
| `config/Module.symvers` | 官方 9 个 vendor ko 提取的 635 个真实 CRC |
| `kernel_module/` | S15 kernel_module 复制 + K7x 符号表全量逆向 |
| `kernel_module/infra/s15_addr.c` | 43 符号表：41 项有值（RELA/kallsyms/别名），2 项 4.14 不存在留 0 |

符号表关键项：
- `init_task=0x201D0C0`、`init_cred=0x202A9E8`
- `sys_call_table=0x10E2000`（RELA 435 连续 sys_* 指针）
- `selinux_state=0xA0F2710`、`security_hook_heads=0xA52CB10`
- `mod_verify_sig` patch 偏移另在 ghostlock 侧（`0x104C44`）

## 构建

推送到 `main` 或在 Actions 页手动触发 `build-k7x-ksu-raw`。
脚本从 fork `yaohewoma/android_kernel_mtk6853` 的 `k7x-ksu-build` 分支拉 4.14 内核树，
用真机 config + 真机 symvers 做 `modules_prepare` 后编 external module。
产物 `ksu_raw.ko` 在 Artifacts（`k7x-ksu-raw`）。

## 校验

编出后比对：
- vermagic 应为 `4.14.186+ SMP preempt mod_unload modversions aarch64`
- `modpost` 不应有 `no symbol version` 警告（CRC 来自真机 symvers）
- `undefined_symbols.txt` 里的符号必须都在真机内核导出表里

## 注意

- 这是**临时 root** 的一个组件，不刷分区、不写 boot/system。
- 即便 ko 编出，最终能否用仍依赖真机验证：ghostlock 写原语能否写 .text（STRICT_KERNEL_RWX）。
- `--sig` 在 K7x 上走 mod_verify_sig patch（不是 sig_enforce），逻辑待真机验证后加入 ghostlock。
