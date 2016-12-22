#!/bin/bash
set -ev

# Install from homebrew
brew outdated cmake || brew upgrade cmake
brew install qt5 p7zip ninja lcov

# Install other dependencies
pushd dependencies

export VLC_VERSION=2.2.4

# Install VLC
curl -LO http://download.videolan.org/vlc/${VLC_VERSION}/macosx/vlc-${VLC_VERSION}.dmg
hdiutil attach vlc-${VLC_VERSION}.dmg

export PATH=/usr/local/opt/qt5/bin:$PATH

popd
