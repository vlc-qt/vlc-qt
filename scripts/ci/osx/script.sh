#!/bin/bash
set -ev

# Configure and build
pushd build
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../install/ \
	-DWITH_HOMEBREW=ON -DCOVERAGE=ON \
	-DLIBVLC_INCLUDE_DIR=/Volumes/vlc-2.2.2/VLC.app/Contents/MacOS/include \
	-DLIBVLC_LIBRARY=/Volumes/vlc-2.2.2/VLC.app/Contents/MacOS/lib/libvlc.dylib \
	-DLIBVLCCORE_LIBRARY=/Volumes/vlc-2.2.2/VLC.app/Contents/MacOS/lib/libvlccore.dylib
ninja prepare
cmake ..
ninja -v
ninja coverage -v
ninja install -v
popd

# Configure and build statically
pushd build-static
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../install/ \
    -DSTATIC=ON -DWITH_HOMEBREW=ON \
	-DLIBVLC_INCLUDE_DIR=/Volumes/vlc-2.2.2/VLC.app/Contents/MacOS/include \
	-DLIBVLC_LIBRARY=/Volumes/vlc-2.2.2/VLC.app/Contents/MacOS/lib/libvlc.dylib \
	-DLIBVLCCORE_LIBRARY=/Volumes/vlc-2.2.2/VLC.app/Contents/MacOS/lib/libvlccore.dylib
ninja prepare
cmake ..
ninja -v
ninja test -v
ninja install -v
popd
