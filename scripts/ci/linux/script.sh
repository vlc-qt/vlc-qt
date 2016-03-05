#!/bin/bash
set -ev

# Configure and build
pushd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install/ -DQT_VERSION=$QT_VERSION -DBUILD_TESTS=ON -DLIBVLC_VERSION=0x020000
make
make install
popd

# Test run (Qt4 only)
if [ $QT_VERSION -eq 4 ]
then
    LD_LIBRARY_PATH=install/lib/ install/bin/VLC-Qt test
fi
