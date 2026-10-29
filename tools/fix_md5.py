#!/usr/bin/env python3
"""重算 md5.xml，避免游戏内 checkMD5() 校验失败直接退出。"""
import os, re, sys, hashlib

res = sys.argv[1] if len(sys.argv) > 1 else "work/Resources"
path = os.path.join(res, "Element", "md5.xml")
if not os.path.exists(path):
    print("md5.xml not found:", path); sys.exit(0)

def md5(p):
    h = hashlib.md5()
    with open(p, "rb") as f:
        for c in iter(lambda: f.read(1 << 20), b""):
            h.update(c)
    return h.hexdigest()

txt = open(path, "rb").read().decode("utf-8", errors="replace")
changed = 0

def repl(m):
    global changed
    src = m.group(1)
    old = m.group(2)
    p = os.path.join(res, src)
    if not os.path.exists(p):
        print("MISSING", src)
        return m.group(0)
    new = md5(p)
    if new != old:
        changed += 1
        print("FIX", src, old, "->", new)
    return '<path src="%s">%s</path>' % (src, new)

txt2 = re.sub(r'<path src="([^"]+)">([0-9a-f]{32})</path>', repl, txt)
open(path, "wb").write(txt2.encode("utf-8"))
print("md5.xml updated, changed:", changed)
