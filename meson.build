project('gamemode-libdbus',
        'c',
        version: '0.1.0',
        meson_version: '>= 0.46.0',
        default_options: ['warning_level=1',
                          'c_std=gnu11',
                          'buildtype=debugoptimized',
                          'b_asneeded=false']
)

cc = meson.get_compiler('c')

#dependencies

pkg  = import('pkgconfig')
dl   = cc.find_library('dl', required: true)
dbus = dependency('dbus-1')

prefixdir = get_option('prefix')
libdir = join_paths(prefixdir, get_option('libdir'))
pkgconfigdir = join_paths(libdir, 'pkgconfig')

hdrsubdir = 'gamemode-libdbus'

conf = configuration_data()
conf.set_quoted('VERSION', meson.project_version())
conf.set_quoted('PACKAGE_VERSION', meson.project_version())

configure_file(
  output: 'config.h',
  configuration: conf,
)

add_project_arguments([
  '-I' + meson.build_root(),
], language: 'c')

# lib
lib_current = '0'
lib_revision = '0'
lib_age = '0'
lib_version = '@0@.@1@.@2@'.format(lib_current, lib_age, lib_revision)

gamemode = shared_library(
  'gamemode',
	['gamemode.c'],
	dependencies: [dbus],
	install: true,
	soversion: lib_current,
	version: lib_version)

install_headers(['gamemode_client.h'], subdir: hdrsubdir)

pkg.generate(
  name: 'gamemode-libdbus',
  description: 'GameMode client library using libdbus',
  version: meson.project_version(),
  libraries_private: [dl],
  install_dir: pkgconfigdir,
  subdirs: [hdrsubdir],
)

gamemode_auto = shared_library(
  'gamemodeauto',
	['gamemode-auto.c'],
	dependencies: [dl],
	install: true,
	soversion: lib_current,
	version: lib_version)

pkg.generate(gamemode_auto,
  name: 'gamemodeauto-libdbus',
  description: 'GameMode client library using libdbus',
  version: meson.project_version(),
  libraries_private: [dl, '-Wl,--no-as-needed'],
  install_dir: pkgconfigdir,
  subdirs: [hdrsubdir],
)

# examples

gm_auto = declare_dependency(
  link_with: [gamemode_auto],
  include_directories: [
    include_directories('.')
])

executable('gm-auto',
  ['examples/auto.c'],
  dependencies: [gm_auto],
  install: false)
