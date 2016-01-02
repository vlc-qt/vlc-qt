# Building VLC-Qt

## Requirements
VLC-Qt can be built with any common compiler (g++, clang, MSVC, MinGW).
Build files are generated using [CMake](http://www.cmake.org) (3.0.2 or later).

All stable versions of VLC since 2.0 work with VLC-Qt.
Both Qt version 4 (4.8 or later) and 5 (5.2 or later) are supported but
can not be used at the same time. Binaries will always be provided for latest Qt version
released at the time of release. Note that Qt4 may require some manual intervention
when installing.

## CMake configuration
There are some specific CMake flags may need:

 * `BUILD_TESTS`: build test application, OFF by default
 * `DEBUG_SUFFIX`: add debug suffix 'd' to the libraries, ON on Widows, OFF elsewhere
 * `LIBVLC_VERSION`: set VLC version you are compiling with to disable unsupported
 	features, should be defined as base 16 integer like `0x020200`, defaults to
 	latest stable VLC version
 * `STATIC`: build statically, OFF by default

Building in separate `build` directory is recommended.

## Platform specific instructions
### OS X
You need to prepare VLC libraries and plugins before building. After `cmake` run
`make prepare`, then re-run `cmake`. Build as a normal library or application.
DMG for test app can be made by running `make dmg`.

Supported generators are `make` and `ninja`.
Qt in `PATH` and VLC in `/Applications` will be used.

Make example:
```
$ export PATH=$PATH:/path/to/Qt/5.5/clang_64/bin
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON
$ make prepare
$ cmake ..
$ make -j8
$ make install
$ make dmg
```

### Windows
Build as a normal library or application. Install required libraries using
`make windows`.

Make sure you always use debug libraries with debug build and release libraries
with release build after using it in your project.

Supported generators for MSVC are `nmake`, `jom` and `ninja`;
for MinGW: `mingw32-make` and `ninja`.
Run specific Qt shell to select its version. VLC path needs to be specified manually.

Ninja example for MSVC64:
```
$ md build
$ cd build
$ cmake .. -G "NMake Makefiles JOM" -DCMAKE_BUILD_TYPE=Debug ^
  -DCMAKE_INSTALL_PREFIX="E:/install/vlc-qt/msvc64" ^
  -DLIBVLC_LIBRARY="E:/vlc/win64/sdk/lib/libvlc.lib" ^
  -DLIBVLCCORE_LIBRARY="E:/vlc/win64/sdk/lib/libvlccore.lib" ^
  -DLIBVLC_INCLUDE_DIR="E:/vlc/win64/sdk/include"
$ ninja
$ ninja install
$ ninja windows
```

### Linux
Install requirements from your distribution's repository.
Supported generators are `make` and `ninja`.

Make example:
```
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON
$ make -j8
$ make install
```
