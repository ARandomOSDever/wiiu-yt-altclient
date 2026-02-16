#!/usr/bin/env python3
from os.path import exists as fileExists

if not fileExists("extlibsDLs.txt"):
    print("")
    pass

infile = open("extlibsDLs.txt")