project('yt-altclient', ['c', 'cpp'])

if host_machine.system() == 'cafeos'

devkitpro = '/opt/devkitpro'
elf2rpl = devkitpro / 'tools/bin/elf2rpl'
pname = meson.project_name()

sources = []
dependencies = []
dependencies += dependency('sdl2')
dependencies += dependency('SDL2_ttf')
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