#!/bin/bash
set -ev

# Report code coverage
bash <(curl -s https://codecov.io/bash) -f build/coverage.info

# Deploy builds
pushd install
7z a VLC-Qt.7z lib > /dev/null

pushd artifacts
mv ../VLC-Qt.7z VLC-Qt_${VLCQT_VERSION}_build${TRAVIS_BUILD_NUMBER}_${TRAVIS_COMMIT:0:7}.7z

popd
popd
