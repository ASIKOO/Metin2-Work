#! /usr/bin/env python

"""Python utility to print MD5 checksums of argument files.

Works with Python 1.5.2 and later.
"""

import sys, md5

BLOCKSIZE = 1024*1024

def hexify(s):
    return ("%02x"*len(s)) % tuple(map(ord, s))

def main():
    args = sys.argv[1:]
    if not args:
        sys.stderr.write("usage: %s file ...\n" % sys.argv[0])
        sys.exit(2)
    for file in sys.argv[1:]:
        f = open(file, "rb")
        sum = md5.new()
        while 1:
            block = f.read(BLOCKSIZE)
            if not block:
                break
            sum.update(block)
        f.close()
        print hexify(sum.digest()), file

if __name__ == "__main__":
    main()
