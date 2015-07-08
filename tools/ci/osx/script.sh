#!/bin/bash
set -ev

# Configure and build release
pushd build-release
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install/ -DCI=ON -DBUILD_TESTS=ON \
	-DLIBVLC_INCLUDE_DIR=../dependencies/VLC.app/Contents/MacOS/include \
	-DLIBVLC_LIBRARY=../dependencies/VLC.app/Contents/MacOS/lib/libvlc.dylib \
	-DLIBVLCCORE_LIBRARY=../dependencies/VLC.app/Contents/MacOS/lib/libvlccore.dylib
make
make install
popd

# Configure and build debug
pushd build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../install-debug/ -DCI=ON \
	-DLIBVLC_INCLUDE_DIR=../dependencies/VLC.app/Contents/MacOS/include \
	-DLIBVLC_LIBRARY=../dependencies/VLC.app/Contents/MacOS/lib/libvlc.dylib \
	-DLIBVLCCORE_LIBRARY=../dependencies/VLC.app/Contents/MacOS/lib/libvlccore.dylib
make
make install
popd

cp install-debug/lib/vlc-qt-core.framework/Versions/${VLCQT_VERSION}/vlc-qt-core install-debug/lib/vlc-qt-core.framework/Versions/${VLCQT_VERSION}/vlc-qt-core_debug
cp install-debug/lib/vlc-qt-qml.framework/Versions/${VLCQT_VERSION}/vlc-qt-qml install-debug/lib/vlc-qt-qml.framework/Versions/${VLCQT_VERSION}/vlc-qt-qml_debug
cp install-debug/lib/vlc-qt-widgets.framework/Versions/${VLCQT_VERSION}/vlc-qt-widgets install-debug/lib/vlc-qt-widgets.framework/Versions/${VLCQT_VERSION}/vlc-qt-widgets_debug


# Prepare for deployment
pushd build-release
make dmg
popd

# Test execution
pushd install
VLC-Qt.app/Contents/MacOS/VLC-Qt test
popd
