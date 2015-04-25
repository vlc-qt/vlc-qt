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
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../install/ -DCI=ON \
	-DLIBVLC_INCLUDE_DIR=../dependencies/VLC.app/Contents/MacOS/include \
	-DLIBVLC_LIBRARY=../dependencies/VLC.app/Contents/MacOS/lib/libvlc.dylib \
	-DLIBVLCCORE_LIBRARY=../dependencies/VLC.app/Contents/MacOS/lib/libvlccore.dylib
make

mkdir -p ../install/VLC-Qt.app/Contents/MacOS/debug
cp src/core/libvlc-qt.dylib ../install/VLC-Qt.app/Contents/MacOS/debug
cp src/qml/libvlc-qt-qml.dylib ../install/VLC-Qt.app/Contents/MacOS/debug
cp src/widgets/libvlc-qt-widgets.dylib ../install/VLC-Qt.app/Contents/MacOS/debug
popd

# Prepare for deployment
pushd install
macdeployqt VLC-Qt.app -dmg
popd
