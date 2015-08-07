#!/bin/bash
set -ev

# Configure and build with Qt5
pushd build-qt5
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install-qt5/ -DQT_VERSION=5 -DBUILD_TESTS=ON -DLIBVLC_VERSION=0x020000
make
make install
popd

# Configure and build with Qt4
pushd build-qt4
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install-qt4/ -DQT_VERSION=4 -DBUILD_TESTS=ON -DLIBVLC_VERSION=0x020000
make
make install
popd

# Prepare for deployment
pushd install-qt5
tar -jcf VLC-Qt.tar.bz2 *
popd

pushd install-qt4
tar -jcf VLC-Qt.tar.bz2 *
popd

# Test run (Qt4 only)
LD_LIBRARY_PATH=install-qt4/lib/ install-qt4/bin/VLC-Qt test
