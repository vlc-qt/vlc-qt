# Building VLC-Qt

## Requirements
VLC-Qt can be built with any common compiler (g++, clang, MSVC, MinGW).
Build files are generated using [CMake](http://www.cmake.org) (3.0.2 or later).

All stable versions of VLC since 2.1 work with VLC-Qt.
Qt 5 (version 5.5 or later recommende) is recommended as Qt 4 support is
considered deprecated. Binaries will always be provided for latest Qt version
released at the time of release.

**Make sure you have git submodules initialised or you may experience build issues.**

## CMake configuration
There are some specific CMake flags may need:

 * `COVERAGE`: generate coverage report, OFF by default
 * `DEBUG_SUFFIX`: add debug suffix 'd' to the libraries, ON on Widows, OFF elsewhere
 * `LIBVLC_VERSION`: set VLC version you are compiling with to disable unsupported
 	features, should be defined as base 16 integer like `0x020200`, defaults to
 	latest stable VLC version
 * `STATIC`: build statically, OFF by default

Extra platform specific flags:
 * `WITH_GLES`: link OpenGL ES v2 on Windows, OFF by default, only needed for
    Qt 5.4 and lower (deprecated)
 * `WITH_HOMEBREW`: let system know you are using Homebrew provided Qt,
    OFF by default, OS X only
 * `WITH_X11`: link with X11, required by some Linux distributions, OFF by default

Building in separate `build` directory is recommended.
There is a `test` target to run automatic tests for the library.

## Platform specific instructions
### OS X
You need to prepare VLC libraries and plugins before building. After `cmake` run
`make prepare`, then re-run `cmake`. Build as a normal library or application.

Supported generators are `make` and `ninja`.
Qt in `PATH` and VLC in `/Applications` will be used.

Make example:
```
$ export PATH=$PATH:/path/to/Qt/5.6/clang_64/bin
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Debug
$ make prepare
$ cmake ..
$ make -j8
$ make install
```

### Windows
Build as a normal library or application.

Make sure you always use debug libraries with debug build and release libraries
with release build after using it in your project.

Supported generators for MSVC are `nmake`, `jom` and `ninja`;
for MinGW: `mingw32-make` and `ninja`.
Run specific Qt shell to select its version. VLC path needs to be specified manually.

Ninja example for MSVC64:
```
$ md build
$ cd build
$ cmake .. -GNinja -DCMAKE_BUILD_TYPE=Debug ^
  -DCMAKE_INSTALL_PREFIX="E:/install/vlc-qt/msvc64" ^
  -DLIBVLC_LIBRARY="E:/vlc/win64/sdk/lib/libvlc.lib" ^
  -DLIBVLCCORE_LIBRARY="E:/vlc/win64/sdk/lib/libvlccore.lib" ^
  -DLIBVLC_INCLUDE_DIR="E:/vlc/win64/sdk/include"
$ ninja
$ ninja install
```

### Linux
Install requirements from your distribution's repository.
Supported generators are `make` and `ninja`.

Make example:
```
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Debug
$ make -j8
$ make install
```
