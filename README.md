VLC-Qt Library
====================================
VLC-Qt is a free library used to connect Qt and libvlc libraries.
It contains core classes for main media playback and also some GUI
classes for faster media player developement.

VLC-Qt runs on Linux and Windows,
other operating systems are currently not supported.


Get VLC-Qt
----------
You can download VLC-Qt from the official web page
(http://projects.tano.si) or using Git:

    $ git clone git://github.com/ntadej/vlc-qt.git


Dependencies
------------
- g++, make
- cmake >= 2.8.6
- Qt >= 4.8
- libvlc >= 2.0


Compilation
-----------
    $ mkdir build
    $ cd build
    $ cmake .. -DCMAKE_INSTALL_PREFIX=prefix
    $ make


Installation
------------
    $ make install


Copyright info
--------------
Copyright (C) 2010-2013 Tadej Novak

VLC-Qt is free (libre) software. This means that the library
source code is available to public, anyone is welcome to research
how the application works, participate in its development, freely
distribute the application and spread the word!

This project may be used under the terms of the
GNU Lesser General Public License version 3.0 as published by the
Free Software Foundation and appearing in the file LICENSE.LGPL.
