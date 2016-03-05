#!/bin/bash
set -ev

# Configure and build debug build
pushd build
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../install/ \
	-DBUILD_TESTS=ON -DHOMEBREW=ON \
	-DLIBVLC_INCLUDE_DIR=../dependencies/VLC.app/Contents/MacOS/include \
	-DLIBVLC_LIBRARY=../dependencies/VLC.app/Contents/MacOS/lib/libvlc.dylib \
	-DLIBVLCCORE_LIBRARY=../dependencies/VLC.app/Contents/MacOS/lib/libvlccore.dylib
ninja prepare
cmake ..
ninja -v
ninja install -v
ninja dmg -v
popd
