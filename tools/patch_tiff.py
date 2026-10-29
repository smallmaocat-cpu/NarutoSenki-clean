#!/usr/bin/env python3
"""把 cocos2d-x CCImageCommon_cpp.h 里的 TIFF 实现整段禁用（arm64 构建不需要 tiff）。"""
import sys

p = sys.argv[1]
src = open(p, encoding="utf-8", errors="replace").read().splitlines(True)

try:
    a = next(i for i, l in enumerate(src) if "_tiffReadProc" in l and "static" in l)
    b = next(i for i, l in enumerate(src) if "_initWithRawData" in l)
except StopIteration:
    print("PATTERN-NOT-FOUND")
    sys.exit(0)

out = src[:a] + ["#if 0\n"] + src[a:b] + ["#endif\n"] + src[b:]
open(p, "w", encoding="utf-8").write("".join(out))
print("TIFF-BLOCK-DISABLED lines %d-%d" % (a + 1, b))
