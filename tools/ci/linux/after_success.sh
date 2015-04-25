#!/bin/bash
set -ev

# Deploy builds
pushd install-qt5
curl --ftp-create-dirs -m 250 --retry 3 -T VLC-Qt.tar.bz2 -u $FTP_USER:$FTP_PASSWORD ftp://ftp.tano.si/vlc-qt/ci/linux/VLC-Qt_${VLCQT_VERSION}_build${TRAVIS_BUILD_NUMBER}_${TRAVIS_COMMIT:0:7}_qt5.tar.bz2
popd

pushd install-qt4
curl --ftp-create-dirs -m 250 --retry 3 -T VLC-Qt.tar.bz2 -u $FTP_USER:$FTP_PASSWORD ftp://ftp.tano.si/vlc-qt/ci/linux/VLC-Qt_${VLCQT_VERSION}_build${TRAVIS_BUILD_NUMBER}_${TRAVIS_COMMIT:0:7}_qt4.tar.bz2
popd
