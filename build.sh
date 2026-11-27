#!/usr/bin/env bash
# OPPO K7x (PERM00, MT6853, 4.14.186+) KernelSU LKM builder — Ubuntu GH Actions.
#
# Strategy (same as the verified S15 flow):
#   1. fetch a 4.14.186 MTK kernel tree (our fork, k7x-ksu-build branch)
#   2. install real device config + real Module.symvers (635 CRCs from official modules)
#   3. make modules_prepare  (only builds scripts/generated headers, NOT the full kernel)
#   4. feed the real Module.symvers so modpost gets exact CRCs
#   5. make M=<kernel_module> modules -> ksu_raw.ko
#
# The tree is a GKI-generation fork, so a FULL kernel build would fail with
# OPPO_HANS undefined symbols. modules_prepare does not link those, so it is
# safe here — we only need headers + generated autoconf.
set -euo pipefail

TREE_URL="${TREE_URL:-https://github.com/yaohewoma/android_kernel_mtk6853.git}"
TREE_BRANCH="${TREE_BRANCH:-k7x-ksu-build}"
WORK="$PWD/work"
TREE="$WORK/kernel"
MOD="$PWD/kernel_module"
OUT="$PWD/out"
CFG="$PWD/config"

mkdir -p "$WORK" "$OUT"

echo "== [1/6] fetch 4.14 kernel tree"
if [ ! -d "$TREE/scripts" ]; then
    git clone --depth 1 --branch "$TREE_BRANCH" "$TREE_URL" "$TREE"
fi
test -f "$TREE/Makefile" || { echo "FATAL: tree incomplete"; exit 1; }
head -5 "$TREE/Makefile"

echo "== [2/6] deps"
sudo apt-get update -qq
sudo apt-get install -y -qq gcc-aarch64-linux-gnu bison flex bc libssl-dev libelf-dev cpio > /dev/null

echo "== [3/6] install device config"
cp "$CFG/k7x_defconfig" "$TREE/.config"
python3 - "$TREE/.config" <<'PYEOF'
import sys
p = sys.argv[1]
s = open(p).read()
lines = s.split('\n')
def setcfg(name, val):
    global lines
    lines = [l for l in lines if not l.startswith(name + '=') and not l.startswith('# ' + name)]
    lines.append(val)
# module build essentials
setcfg('CONFIG_MODULES', 'CONFIG_MODULES=y')
setcfg('CONFIG_MODVERSIONS', 'CONFIG_MODVERSIONS=y')
setcfg('CONFIG_KALLSYMS', 'CONFIG_KALLSYMS=y')
setcfg('CONFIG_LOCALVERSION', 'CONFIG_LOCALVERSION=""')
lines = [l for l in lines if l.strip() != '# CONFIG_LOCALVERSION_AUTO is not set']
lines.append('# CONFIG_LOCALVERSION_AUTO is not set')
open(p, 'w').write('\n'.join(lines))
print('config patched for module build')
PYEOF
grep -E '^CONFIG_(MODULES|MODVERSIONS|KALLSYMS|LOCALVERSION)=' "$TREE/.config" || true

cd "$TREE"
export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-

echo "== [4/6] olddefconfig + modules_prepare"
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- olddefconfig > "$OUT/olddefconfig.log" 2>&1 || {
    tail -40 "$OUT/olddefconfig.log"; exit 1; }
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- modules_prepare -j"$(nproc)" > "$OUT/prepare.log" 2>&1 || {
    tail -60 "$OUT/prepare.log"; exit 1; }
tail -8 "$OUT/prepare.log"

echo "== [5/6] feed real CRC symvers"
# selinux generated headers (some trees need them for module includes)
if [ -x "$TREE/scripts/selinux/genheaders/genheaders" ]; then
    "$TREE/scripts/selinux/genheaders/genheaders" \
        "$TREE/security/selinux/flask.h" "$TREE/security/selinux/av_permissions.h" || true
    cp "$TREE/security/selinux/flask.h" "$TREE/security/selinux/include/flask.h" 2>/dev/null || true
    cp "$TREE/security/selinux/av_permissions.h" "$TREE/security/selinux/include/av_permissions.h" 2>/dev/null || true
fi
cp "$CFG/Module.symvers" "$TREE/Module.symvers"
echo "real symvers: $(wc -l < "$CFG/Module.symvers") symbols"

echo "== [6/6] build kernel_module"
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- M="$MOD" modules -j"$(nproc)" \
    > "$OUT/build.log" 2>&1 || { tail -80 "$OUT/build.log"; exit 1; }

KO="$MOD/ksu_raw.ko"
test -f "$KO" || { echo "FATAL: $KO not produced"; tail -60 "$OUT/build.log"; exit 1; }
aarch64-linux-gnu-strip -d "$KO" 2>/dev/null || true
cp "$KO" "$OUT/ksu_raw.ko"

echo "== diagnostics"
aarch64-linux-gnu-nm -u "$KO" > "$OUT/undefined_symbols.txt" 2>&1 || true
echo "undefined symbols: $(wc -l < "$OUT/undefined_symbols.txt")"
grep -E "no symbol version|WARNING" "$OUT/build.log" | head -40 > "$OUT/modpost_warnings.txt" || true
cp "$TREE/.config" "$OUT/built_config"
cp "$MOD/Module.symvers" "$OUT/module_Module.symvers" 2>/dev/null || true

ls -la "$OUT/ksu_raw.ko"
sha256sum "$OUT/ksu_raw.ko"
echo "BUILD_OK"
