#!/bin/bash
set -ev

# Configure and build with Qt5
pushd build-qt5
cmake .. -DQT_VERSION=5 -DBUILD_TESTS=ON
make
popd

# Configure and build with Qt4
pushd build-qt4
cmake .. -DQT_VERSION=4 -DBUILD_TESTS=ON
make
popd
