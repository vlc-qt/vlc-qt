# VLC-Qt Library
[![Homepage][web-img]][web]
[![Latest release][release-img]][release]
[![License][license-img]][license]
[![Build Status][travis-img]][travis]

VLC-Qt is a free library used to connect [Qt](http://qt.io) and
[libVLC](http://videolan.org) libraries. It contains core classes for main
media playback and also some GUI classes for faster media player development.

VLC-Qt runs on supported versions of Linux, OS X and Windows. It is developed
in cross-platform spirit so it may work on other systems but is not supported.


## Binaries and source code

You can download VLC-Qt binaries and sources from the [official web page]
(http://vlc-qt.tano.si).

Latest source is also available via Git:
```bash
  git clone git://github.com/ntadej/vlc-qt.git
```

Master branch is considered stable and working on all supported platforms.
All development is made in branches. You can also find specific releases by
browsing tags.


## Examples and guides
VLC-Qt examples are now located in the [examples](https://github.com/vlc-qt/examples)
repository.

A special guides section will be introduced on the web page soon.


## Requirements

VLC-Qt can be built with any common compiler (g++, clang, MSVC, MinGW).
Build files are generated using [CMake](http://www.cmake.org) (3.0.2 or later).

All stable versions of VLC since 2.0 work with VLC-Qt.
Both Qt version 4 (4.8 or later) and 5 (5.2 or later) are supported but
can not be used at the same time.


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
[release]: https://github.com/ntadej/vlc-qt/releases
[license]: https://github.com/ntadej/vlc-qt/blob/master/LICENSE.md
[travis]: https://travis-ci.org/ntadej/vlc-qt

[web-img]: https://img.shields.io/badge/web-vlc--qt.tano.si-green.svg
[license-img]: https://img.shields.io/github/license/ntadej/vlc-qt.svg
[release-img]: https://img.shields.io/github/release/ntadej/vlc-qt.svg
[travis-img]: https://travis-ci.org/ntadej/vlc-qt.svg?branch=master
