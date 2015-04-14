#!/bin/bash
set -ev

# Install dependencies from APT
sudo apt-get update -qq
sudo apt-get install -y libqt4-dev libvlc-dev libvlccore-dev p7zip-full


# Install other dependencies
pushd dependencies

# Install CMake 3.2.1
wget http://www.cmake.org/files/v3.2/cmake-3.2.1-Linux-x86_64.tar.gz

tar xf cmake-3.2.1-Linux-x86_64.tar.gz

# Install Qt 5.4.1
wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_54/qt.54.gcc_64/5.4.1-0qt5_essentials.7z
wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_54/qt.54.gcc_64/5.4.1-0qt5_essentials.7z.sha1
wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_54/qt.54.gcc_64/5.4.1-0icu_53_1_ubuntu_11_10_64.7z
wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_54/qt.54.gcc_64/5.4.1-0icu_53_1_ubuntu_11_10_64.7z.sha1

7z x 5.4.1-0qt5_essentials.7z > /dev/null
7z x 5.4.1-0icu_53_1_ubuntu_11_10_64.7z > /dev/null

export PATH=$PWD/cmake-3.2.1-Linux-x86_64/bin/:$PWD/5.4/gcc_64/bin/:$PATH

popd
