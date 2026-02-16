project('yt-altclient', ['c', 'cpp'], default_options : ['cpp_std=c++20','default_library=static'])

if host_machine.system() == 'cafeos'

devkitpro = '/opt/devkitpro'
elf2rpl = devkitpro / 'tools/bin/elf2rpl'
pname = meson.project_name()
cc = meson.get_compiler('c')

sources = []
dependencies = []
dependencies += dependency('sdl2')
dependencies += dependency('SDL2_ttf')
dependencies += dependency('libpng')
dependencies += dependency('zlib')
dependencies += cc.find_library('bz2') # i'm having issues with the bz2 wrap
dependencies += dependency('libbrotlidec')
dependencies += dependency('nlohmann_json')

subdir('src')


elf = executable(pname + '.elf', sources, dependencies : dependencies, include_directories : include_directories('include'))

custom_target('RPX',
          depends : elf,
          input : elf,
          output : pname + '.rpx',
          command : [elf2rpl, '@INPUT@', '@OUTPUT@'],
          build_by_default : true)
else
error('must cross compile with crossfile.ini: \n\tmeson setup build --cross-file crossfile.ini')
endif