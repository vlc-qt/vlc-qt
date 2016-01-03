#!/bin/bash
set -ev

# Deploy builds
pushd install
tar -jcf VLC-Qt.tar.bz2 *

mkdir artifacts
mv VLC-Qt.tar.bz2 artifacts/VLC-Qt_${VLCQT_VERSION}_build${TRAVIS_BUILD_NUMBER}_${TRAVIS_COMMIT:0:7}_qt${QT_VERSION}.tar.bz2
popd
