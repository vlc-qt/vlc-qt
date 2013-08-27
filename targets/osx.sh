VER=`cat VERSION`
PWD=`pwd`
BUILD_DIR="${PWD}/release/build"
OUTPUT_DIR="${PWD}/release/VLC-Qt_${VER}_OSX10.6"
ARCHIVE_DIR="${PWD}/release"

build() 
{
    say "Building VLC-Qt"

    if [ -d "${OUTPUT_DIR}" ]; then
        rm -r ${OUTPUT_DIR}
    fi
    mkdir -p ${BUILD_DIR}
    mkdir -p ${OUTPUT_DIR}

    pushd ${BUILD_DIR}
    cmake ../../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${OUTPUT_DIR} -DLIBVLC_INCLUDE_DIR=/Applications/VLC.app/Contents/MacOS/include -DLIBVLC_LIBRARY=/Applications/VLC.app/Contents/MacOS/lib/libvlc.dylib -DLIBVLCCORE_LIBRARY=/Applications/VLC.app/Contents/MacOS/lib/libvlccore.dylib
    make install -j8
    popd

    say "Deploying VLC-Qt"

    pushd ${ARCHIVE_DIR}
    tar -jcvf VLC-Qt_${VER}_OSX10.6.tar.bz2 VLC-Qt_${VER}_OSX10.6
    popd

    say "VLC-Qt deployment completed!"
}

eval build
