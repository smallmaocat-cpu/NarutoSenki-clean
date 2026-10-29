#!/usr/bin/env python3
"""
去掉 arm64 版 .so 里对 libstdc++.so 的 DT_NEEDED 依赖。
Android 5.0+ 已移除 libstdc++.so，而 gnustl_static 已把符号静态链入，
这个依赖纯属链接器残留，会导致 dlopen 失败（表现是 JNI 找不到方法）。
做法：把 .dynstr 里的 "libstdc++.so" 原地改成长度相同的 "libc.so"，libc 本来就已依赖，重复无副作用。
"""
import sys, struct

path = sys.argv[1]
d = bytearray(open(path, "rb").read())

old = b"libstdc++.so\x00"        # 13 字节
new = b"libc.so\x00\x00\x00\x00\x00"  # 7 + 5 = 12... 补齐
# 保证等长：libstdc++.so 是 11 字符 + NUL = 12 字节
old = b"libstdc++.so\x00"
new = b"libc.so\x00\x00\x00\x00\x00"[:len(old)]
if len(new) < len(old):
    new = new + b"\x00" * (len(old) - len(new))

idx = d.find(old)
if idx < 0:
    print("libstdc++.so not found, nothing to patch")
    sys.exit(0)

d[idx:idx + len(old)] = new
open(path, "wb").write(d)
print("patched DT_NEEDED libstdc++.so -> libc.so at offset", idx)
