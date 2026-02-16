project('bzip2', 'c', version: '1.0.8', meson_version: '>=1.0.0')

libbz2_lib = static_library(
    'bz2',
    'blocksort.c',
    'huffman.c',
    'crctable.c',
    'randtable.c',
    'compress.c',
    'decompress.c',
    'bzlib.c',
    #pic: true,
    install: true,
)

install_headers('bzlib.h')

bzip2_dep = declare_dependency(
    link_with: libbz2_lib,
    include_directories: include_directories('.'),
)
meson.override_dependency('bzip2', bzip2_dep)
