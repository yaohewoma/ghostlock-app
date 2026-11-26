# GhostLock S15 交付包

本分支是纯交付仓库（孤立分支 `deliverables`），只放临时 root 工具的成品，不含主源码。

## 文件

| 文件 | 大小 | SHA256 |
|---|---|---|
| `ksu` | 5,201,901 | `c1a5b3a5f8497d7509a6b13dc157f1bced8c1a0916432eed120ba696be644c97` |
| `GhostLock-S15.apk` | 22,475,894 | `ec91f194a429782b852c6c77ec1ba033084958abdefef993176e8bb763c136e7` |

校验清单见 `SHA256SUMS.txt`。

## 手机端拉取（推荐服务器直连，国内快）

服务器托管在国内阿里云，**比 GitHub 镜像更快**，不需要走镜像：

```sh
# ksu 包（带校验）
curl -sL 'http://118.31.17.194:9955/dl/ksu?token=43ZpasqEKBYS_8xQAK5Slv5A' -o ~/ksu
[ "$(sha256sum ~/ksu | cut -d' ' -f1)" = "c1a5b3a5f8497d7509a6b13dc157f1bced8c1a0916432eed120ba696be644c97" ] && echo OK || echo FAIL

# GhostLock APK
curl -sL 'http://118.31.17.194:9955/dl/GhostLock-S15.apk?token=43ZpasqEKBYS_8xQAK5Slv5A' -o ~/GhostLock.apk
```

## GitHub raw 直连 / 镜像（备用）

raw 直连：
```sh
curl -sL 'https://raw.githubusercontent.com/yaohewoma/ghostlock-app/deliverables/ksu' -o ~/ksu
```

国内镜像（把 `URL` 换成下面的前缀 + 上面的 raw 路径）：
- `https://ghproxy.net/`
- `https://gh-proxy.com/`
- `https://github.moeyy.xyz/`

例：
```sh
curl -sL 'https://ghproxy.net/https://raw.githubusercontent.com/yaohewoma/ghostlock-app/deliverables/ksu' -o ~/ksu
```

**拉完必须校验 SHA256**，镜像可能缓存旧版本或被篡改。

## 红线

- 本工具用于临时 root，不刷分区、不写 boot/system。
- 永远不执行 `oem unlock` / `oem verify:`（会删 userdata 密钥）。
