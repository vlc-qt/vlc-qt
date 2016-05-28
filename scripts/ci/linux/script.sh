#!/bin/bash
set -ev

# Configure and build
pushd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install/ -DQT_VERSION=$QT_VERSION -DLIBVLC_VERSION=0x020100
make
# Run tests (Qt5 only) - temporarily removed due to Travis issues
# if [ $QT_VERSION -eq 5 ]
# then
#     make test
# fi
make install
popd

# Configure and build statically
pushd build-static
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install-static/ -DQT_VERSION=$QT_VERSION -DLIBVLC_VERSION=0x020100 -DSTATIC=ON
make
# Run tests (Qt5 only) - temporarily removed due to Travis issues
# if [ $QT_VERSION -eq 5 ]
# then
#     make test
# fi
make install
popd
