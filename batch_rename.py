#!/usr/bin/python

import os
import sys
from optparse import OptionParser

def generate_name(filename, base, num):
    extension = os.path.splitext(filename)[1]
    renamed = '%s%04d%s' % (base, num, extension)
    return renamed

def rename_file(path, filename, output, base, num):
    original = os.path.join(path, filename)
    renamed = generate_name(filename, base, num)
    final = os.path.join(output, base)
    os.rename(original, renamed)
    print '"%s" -> "%s"' % (original, renamed)

def main():
    parser = OptionParser(usage='Usage: %prog -d DIR -b BASE')
    parser.add_option("-d", "--dir", dest="directory",
                      help="rename files in DIR", metavar="DIR")
    parser.add_option("-b", "--base", dest="base",
                      help="start renamed files with BASE", metavar="BASE")
    parser.add_option("-o", "--output", dest="output", help="output directory")

    (options, args) = parser.parse_args()

    if not options.directory:
        parser.error('Directory not given')

    if not options.base:
        parser.error('Base name not given')

    path = options.directory
    base = options.base

    if options.output:
        output = options.output
    else:
        output = path

    files = [f for f in os.listdir(path) if os.path.isfile(os.path.join(path, f))]
    files.sort()

    print 'Renaming files in "%s" with basename "%s"' % (path, os.path.join(output, base))

    for i, f in enumerate(files):
        print '"%s" -> "%s"' % (f, generate_name(f, base, i))

    ans = None
    while (ans not in ['y', 'Y', 'n', 'N', '']):
        ans = raw_input('Proceed? [y/N] ')

    if ans in ['n', 'N', '']:
        return

    num = 0
    for f in files:
        rename_file(path, f, output, base, num)
        num += 1

if __name__ == '__main__':
    main()