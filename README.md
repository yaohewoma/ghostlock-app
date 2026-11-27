# GhostLock S15 交付包

本分支是纯交付仓库（孤立分支 `deliverables`），只放临时 root 工具的成品，不含主源码。

## 文件

| 文件 | 大小 | SHA256 |
|---|---|---|
| `ksu` | 5,201,901 | `c1a5b3a5f8497d7509a6b13dc157f1bced8c1a0916432eed120ba696be644c97` |
| `GhostLock-S15.apk` | 22,408,854 | `d310189b37553abe606d341f159e70bef7a797773ad85cf93b6bfb2a04dcbf5d` |

校验清单见 `SHA256SUMS.txt`。

## ★最简单：App 内直接拉（无需 Termux / 命令行）

安装 APK 后，进第二个 Tab「S15 KSU 全家桶」→ 机型选 vivo S15 → 点「**从服务器拉取验证包**」。
App 会自动从服务器下载 ksu 包、校验 SHA256（内置权威 hash `c1a5…644c97`）、校验通过后自动设为已选包，
然后直接点「一键执行 KSU 全家桶」即可。全程手机操作，不用电脑、不用 Termux、不用传文件。

只有 Shizuku 授权需要在 App 内点一下（KSU 页 Shizuku 行可点击）。

## 手机端命令行拉取（备用；服务器直连，国内快）

服务器托管在国内阿里云，**比 GitHub 镜像更快**，不需要走镜像：

```sh
# ksu 包（带校验）
curl -sL 'http://118.31.17.194:9955/dl/ksu?token=43ZpasqEKBYS_8xQAK5Slv5A' -o ~/ksu
[ "$(sha256sum ~/ksu | cut -d' ' -f1)" = "c1a5b3a5f8497d7509a6b13dc157f1bced8c1a0916432eed120ba696be644c97" ] && echo OK || echo FAIL

# GhostLock APK
curl -sL 'http://118.31.17.194:9955/dl/GhostLock-S15.apk?token=43ZpasqEKBYS_8xQAK5Slv5A' -o ~/GhostLock.apk
```

## GitHub 镜像（备用；raw 直连在国内实测失败）

**实测（2026-11-27）**：`raw.githubusercontent.com` 直连返回错误页（39KB，hash 不符），**不要用**；`ghproxy.net` 镜像成功拿到完整 5,201,901 bytes、hash 一致。

推荐镜像（前缀 + raw 路径）：
- `https://ghproxy.net/` ← 实测可用
- `https://gh-proxy.com/`
- `https://github.moeyy.xyz/`

```sh
curl -sL 'https://ghproxy.net/https://raw.githubusercontent.com/yaohewoma/ghostlock-app/deliverables/ksu' -o ~/ksu
[ "$(sha256sum ~/ksu | cut -d' ' -f1)" = "c1a5b3a5f8497d7509a6b13dc157f1bced8c1a0916432eed120ba696be644c97" ] && echo OK || echo FAIL
```

APK 同理，把路径换 `GhostLock-S15.apk`。

**拉完必须校验 SHA256**，镜像可能缓存旧版本或被篡改。国内首选还是上面的服务器直连（更快更稳）。

## 红线

- 本工具用于临时 root，不刷分区、不写 boot/system。
- 永远不执行 `oem unlock` / `oem verify:`（会删 userdata 密钥）。
