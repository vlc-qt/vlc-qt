#!/bin/bash
set -ev

# Deploy builds
pushd install
curl --ftp-create-dirs -m 250 --retry 3 -T VLC-Qt.dmg -u $FTP_USER:$FTP_PASSWORD ftp://ftp.tano.si/vlc-qt/ci/osx/VLC-Qt_${VLCQT_VERSION}_build${TRAVIS_BUILD_NUMBER}_${TRAVIS_COMMIT:0:7}.dmg
popd
