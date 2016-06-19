# VLC-Qt Library [![Build Status][travis-img]][travis] [![Build status][appveyor-img]][appveyor]
[![Homepage][web-img]][web]
[![Latest release][release-img]][release]
[![Download][download-img]][download]
[![License][license-img]][license]
[![codecov.io][codecov-img]][codecov]

VLC-Qt is a free library used to connect [Qt](http://qt.io) and
[libVLC](http://videolan.org) libraries. It contains core classes for main
media playback and also some GUI classes for faster media player development.

VLC-Qt runs on supported versions of Linux, OS X and Windows. It is developed
in cross-platform spirit so it may work on other systems but is not supported.

## VLC-Qt 1.1 Qt/VLC versions deprecation warning
**Since 1.1 release, support for some older Qt and VLC versions will be removed
or deprecated:**
 - Qt 4 support will be deprecated and removed in 2.0
 - Qt 5 lower than 5.5 will be deprecated and removed in 2.0
 - libVLC 2.1 will be required

## Binaries and source code
You can download VLC-Qt binaries and sources from the
[official web page](https://vlc-qt.tano.si) or
[GitHub releases](https://github.com/vlc-qt/vlc-qt/releases).

Latest source is also available via Git:
```bash
  git clone git://github.com/vlc-qt/vlc-qt.git
  git submodule init
  git submodule update
```

Master branch is considered stable and working on all supported platforms.
All development is made in branches. You can also find specific releases by
browsing tags.


## Examples and guides
VLC-Qt examples are now located in the [examples](https://github.com/vlc-qt/examples)
repository.

All discussions that are not bug related can be made [here](https://discuss.tano.si).
This is also a place where you can publish your guides.


## Building and requirements
See [How to build VLC-Qt](BUILDING.md).

## Contributing
There are several ways to contribute to VLC-Qt:
 * [Report a bug](CONTRIBUTING.md#submitting-issues)
 * [Propose a new feature](CONTRIBUTING.md#feature-requests)
 * [Submit a pull-request](CONTRIBUTING.md#pull-requests)
 * [Write a guide](CONTRIBUTING.md#writing-guides)


## Copyright info
Copyright (C) 2010-2016 Tadej Novak

VLC-Qt is free (libre) software. This means that the library
source code is available to public, anyone is welcome to research
how the application works, participate in its development, freely
distribute the application and spread the word!

This project may be used under the terms of the
GNU Lesser General Public License version 3.0 as published by the
Free Software Foundation and appearing in the file [LICENSE.md](LICENSE.md).


[web]: https://vlc-qt.tano.si
[release]: https://github.com/vlc-qt/vlc-qt/releases/latest
[download]: https://github.com/vlc-qt/vlc-qt/releases
[license]: https://github.com/vlc-qt/vlc-qt/blob/master/LICENSE.md
[travis]: https://travis-ci.org/vlc-qt/vlc-qt
[appveyor]: https://ci.appveyor.com/project/ntadej/vlc-qt
[codecov]: https://codecov.io/github/vlc-qt/vlc-qt?branch=master

[web-img]: https://img.shields.io/badge/web-vlc--qt.tano.si-green.svg
[license-img]: https://img.shields.io/github/license/vlc-qt/vlc-qt.svg
[release-img]: https://img.shields.io/github/release/vlc-qt/vlc-qt.svg
[download-img]: https://img.shields.io/github/downloads/vlc-qt/vlc-qt/total.svg
[travis-img]: https://travis-ci.org/vlc-qt/vlc-qt.svg?branch=master
[appveyor-img]: https://ci.appveyor.com/api/projects/status/whnar8rjduiyktkf/branch/master?svg=true
[codecov-img]: https://codecov.io/github/vlc-qt/vlc-qt/coverage.svg?branch=master
