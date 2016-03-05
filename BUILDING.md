# Building VLC-Qt

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
