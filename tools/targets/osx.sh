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
    mkdir -p ${BUILD_DIR}_debug
    mkdir -p ${OUTPUT_DIR}

    pushd ${BUILD_DIR}
    cmake ../../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${OUTPUT_DIR} -DLIBVLC_INCLUDE_DIR=/Applications/VLC.app/Contents/MacOS/include -DLIBVLC_LIBRARY=/Applications/VLC.app/Contents/MacOS/lib/libvlc.dylib -DLIBVLCCORE_LIBRARY=/Applications/VLC.app/Contents/MacOS/lib/libvlccore.dylib -DGIT= -DBUILD_TESTS=ON
    make install -j8
    popd

    pushd ${BUILD_DIR}_debug
    cmake ../../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=${OUTPUT_DIR}_debug -DLIBVLC_INCLUDE_DIR=/Applications/VLC.app/Contents/MacOS/include -DLIBVLC_LIBRARY=/Applications/VLC.app/Contents/MacOS/lib/libvlc.dylib -DLIBVLCCORE_LIBRARY=/Applications/VLC.app/Contents/MacOS/lib/libvlccore.dylib -DGIT=
    make -j8
    popd

    say "Deploying VLC-Qt"

    mkdir ${OUTPUT_DIR}/debug
    mkdir ${OUTPUT_DIR}/examples
    cp ${BUILD_DIR}_debug/src/core/libvlc-qt.dylib ${OUTPUT_DIR}/debug
    cp ${BUILD_DIR}_debug/src/widgets/libvlc-qt-widgets.dylib ${OUTPUT_DIR}/debug
    cp -r examples/ ${OUTPUT_DIR}/examples/
    pushd ${ARCHIVE_DIR}
    tar -jcvf VLC-Qt_${VER}_OSX10.6.tar.bz2 VLC-Qt_${VER}_OSX10.6
    popd

    say "VLC-Qt deployment completed!"
}

eval build
