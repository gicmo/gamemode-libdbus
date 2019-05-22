GameMode client library
=======================

This is a re-implementation of [gamemode][gamemode]'s client library
that very follows the upstream design, but is using the reference
[dbus][dbus] client library (`libdbus-1`) instead of systemd's dbus
implementation. It is meant to be used in situation where systemd
is not around, with flatpak being the most prominent example. It
also has support to use the [desktop portal][portal] if the client
is running inside a flatpak.


Library
=======

The components provided are:

  - `gamemode_client.h`: client loader that provides the source
     level gamemode API. It is a header only component that will load
	 the actual implementation that talkes to the GameMode service at
	 runtime.
  - `libgamemode` shared library: implementation to be loaded at
     runtime via `dlopen` (see above). Will talk to the main GameMode
	 service via dbus (`libdbus-1`) or transparently
	 to the [desktop portal][portal] when running inside a flatpak.
  - `libgamemodeauto` shared library: link-only gamemode integration:
	 it provides integration to GameMode by just linking against it,
	 i.e. no source level integration is needed. As soon as the
	 library is loaded it will request gamemode and end the request
	 when it is unloaded. NB: beware of `-Wl,--as-needed` linker
	 flag (see the ld(1) manpage) the might interfere with properly
	 linking this library.


Examples
========

This package also includes two small examples in the `example`
directory, that show you can give you an idea how to use this
component, or actually [gamemode][gamemode] in general.



[gamemode]: https://github.com/FeralInteractive/gamemode
[dbus]: https://dbus.freedesktop.org/doc/api/html/
[flatpak]: https://flatpak.org/
[portal]: https://github.com/gicmo/xdg-desktop-portal
