#!/bin/bash
set -ev

# Install from homebrew
brew outdated cmake || brew upgrade cmake
brew install qt5 p7zip

# Install other dependencies
pushd dependencies

# Install patched VLC 2.2.1
wget http://download.tano.si/dependencies/vlc/vlc-2.2.1-osx_rpath.7z
7z x vlc-2.2.1-osx_rpath.7z > /dev/null

export PATH=/usr/local/opt/qt5/bin:$PATH

popd
