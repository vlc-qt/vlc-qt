# VLC-Qt Library [![Build Status][travis-img]][travis] [![Build status][appveyor-img]][appveyor]
[![Homepage][web-img]][web]
[![Latest release][release-img]][release]
[![License][license-img]][license]

VLC-Qt is a free library used to connect [Qt](http://qt.io) and
[libVLC](http://videolan.org) libraries. It contains core classes for main
media playback and also some GUI classes for faster media player development.

VLC-Qt runs on supported versions of Linux, OS X and Windows. It is developed
in cross-platform spirit so it may work on other systems but is not supported.

## Important changes

**In preparation for 1.0 release, libraries were renamed and includes prefix changed
to make them fully modular. Please, update CMake search scripts, configure scripts
and/or makefiles before updating to latest version.
See [library reference](http://vlc-qt.tano.si/reference/git/) for more information.**


## Binaries and source code

You can download VLC-Qt binaries and sources from the [official web page]
(http://vlc-qt.tano.si).

Latest source is also available via Git:
```bash
  git clone git://github.com/vlc-qt/vlc-qt.git
```

Master branch is considered stable and working on all supported platforms.
All development is made in branches. You can also find specific releases by
browsing tags.


## Examples and guides
VLC-Qt examples are now located in the [examples](https://github.com/vlc-qt/examples)
repository.

All discussions that are not bug related can be made [here](http://discuss.tano.si).
This is also a place where you can publish your guides.


## Requirements

VLC-Qt can be built with any common compiler (g++, clang, MSVC, MinGW).
Build files are generated using [CMake](http://www.cmake.org) (3.0.2 or later).

All stable versions of VLC since 2.0 work with VLC-Qt.
Both Qt version 4 (4.8 or later) and 5 (5.2 or later) are supported but
can not be used at the same time. Binaries will always be provided for latest Qt version
released at the time of release. Note that Qt4 may require some manual intervention
when installing.


## Building
There are some specific CMake flags may need:

 * `BUILD_TESTS`: build test application, OFF by default
 * `DEBUG_SUFFIX`: add debug suffix 'd' to the libraries, ON on Widows, OFF elsewhere
 * `LIBVLC_VERSION`: set VLC version you are compiling with to disable unsupported
 	features, should be defined as base 16 integer like `0x020200`, defaults to
 	latest stable VLC version
 * `STATIC`: build statically, OFF by default

After running CMake, build with your compiler, depending on makefile generator:
Unix based: `make`, MSVC: `nmake` or `jom`, MinGW: `mingw32-make`

There are two platform specific targets. You can make DMG file on OS X by running
`make dmg` and you can copy required Qt libraries to test with `make windows`.


## Copyright info

Copyright (C) 2010-2015 Tadej Novak

VLC-Qt is free (libre) software. This means that the library
source code is available to public, anyone is welcome to research
how the application works, participate in its development, freely
distribute the application and spread the word!

This project may be used under the terms of the
GNU Lesser General Public License version 3.0 as published by the
Free Software Foundation and appearing in the file LICENSE.md.


[web]: http://vlc-qt.tano.si
[release]: https://github.com/vlc-qt/vlc-qt/releases
[license]: https://github.com/vlc-qt/vlc-qt/blob/master/LICENSE.md
[travis]: https://travis-ci.org/vlc-qt/vlc-qt
[appveyor]: https://ci.appveyor.com/project/ntadej/vlc-qt

[web-img]: https://img.shields.io/badge/web-vlc--qt.tano.si-green.svg
[license-img]: https://img.shields.io/github/license/vlc-qt/vlc-qt.svg
[release-img]: https://img.shields.io/github/release/vlc-qt/vlc-qt.svg
[travis-img]: https://travis-ci.org/vlc-qt/vlc-qt.svg?branch=master
[appveyor-img]: https://ci.appveyor.com/api/projects/status/whnar8rjduiyktkf/branch/master?svg=true
