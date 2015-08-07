#!/bin/bash
set -ev

# Configure and build release
pushd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install/ -DBUILD_TESTS=ON \
	-DLIBVLC_INCLUDE_DIR=../dependencies/VLC.app/Contents/MacOS/include \
	-DLIBVLC_LIBRARY=../dependencies/VLC.app/Contents/MacOS/lib/libvlc.dylib \
	-DLIBVLCCORE_LIBRARY=../dependencies/VLC.app/Contents/MacOS/lib/libvlccore.dylib
make
make install
make dmg
popd

# Test execution
#pushd install/bin
#VLC-Qt.app/Contents/MacOS/VLC-Qt test
#popd
