#!/bin/bash
set -ev

# Configure and build
pushd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install/ -DQT_VERSION=$QT_VERSION -DBUILD_TESTS=ON -DLIBVLC_VERSION=0x020100
make
make install
# Run tests (Qt5 only)
if [ $QT_VERSION -eq 5 ]
then
    make test
fi
popd

# Legacy test run
LD_LIBRARY_PATH=install/lib/ install/bin/VLC-Qt test
