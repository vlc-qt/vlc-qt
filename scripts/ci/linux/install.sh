#!/bin/bash
set -ev

# Install other dependencies
pushd dependencies

# Install CMake 3.4.1
wget https://cmake.org/files/v3.4/cmake-3.4.1-Linux-x86_64.tar.gz

tar xf cmake-3.4.1-Linux-x86_64.tar.gz

export PATH=$PWD/cmake-3.4.1-Linux-x86_64/bin/:$PATH

popd
