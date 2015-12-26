#!/bin/bash
set -ev

# Deploy builds
pushd install-qt5
mv VLC-Qt.tar.bz2 ../install/artifacts/VLC-Qt_${VLCQT_VERSION}_build${TRAVIS_BUILD_NUMBER}_${TRAVIS_COMMIT:0:7}_qt5.tar.bz2
popd

pushd install-qt4
mv VLC-Qt.tar.bz2 ../install/artifacts/VLC-Qt_${VLCQT_VERSION}_build${TRAVIS_BUILD_NUMBER}_${TRAVIS_COMMIT:0:7}_qt4.tar.bz2
popd
