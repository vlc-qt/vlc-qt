#!/bin/bash
set -ev

# Install other dependencies
pushd dependencies

# Install CMake 3.4.1
wget https://cmake.org/files/v3.4/cmake-3.4.1-Linux-x86_64.tar.gz --no-check-certificate

tar xf cmake-3.4.1-Linux-x86_64.tar.gz

# Install Qt 5.5.1
if [ $QT_VERSION -eq 5 ]
then
    wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_55/qt.55.gcc_64/5.5.1-0qt5_essentials.7z
    wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_55/qt.55.gcc_64/5.5.1-0qt5_essentials.7z.sha1
    wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_55/qt.55.gcc_64/5.5.1-0icu-linux-g++-Rhel6.6-x64.7z
    wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_55/qt.55.gcc_64/5.5.1-0icu-linux-g++-Rhel6.6-x64.7z.sha1

    7z x 5.5.1-0qt5_essentials.7z > /dev/null
    7z x 5.5.1-0icu-linux-g++-Rhel6.6-x64.7z > /dev/null

    export PATH=$PWD/5.5/gcc_64/bin/:$PATH
fi

export CC="gcc-4.8"
export CXX="g++-4.8"
export PATH=$PWD/cmake-3.4.1-Linux-x86_64/bin/:$PATH

popd
