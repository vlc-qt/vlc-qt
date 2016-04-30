#!/bin/bash
set -ev

# Install other dependencies
pushd dependencies

# Install CMake 3.5.2
wget https://cmake.org/files/v3.5/cmake-3.5.2-Linux-x86_64.tar.gz

tar xf cmake-3.5.2-Linux-x86_64.tar.gz

export PATH=$PWD/cmake-3.5.2-Linux-x86_64/bin/:$PATH

popd
