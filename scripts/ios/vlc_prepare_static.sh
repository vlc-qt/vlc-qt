#!/bin/bash
#
# Usage:
#   vlc_prepare_static.sh <vlckit-dir> <output-dir> <os-type>
#
# Copies required VLC libraries and plugins to temporary folder in build
# directory and processes them
#

SCRIPT=$(basename "$0")
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd`
popd > /dev/null

INPATH=$1/MobileVLCKit/ImportedSources/vlc/install-ios-iPhone
DIR=$2
TYPE=$3

if [ -z $1 ]; then
    echo "[$SCRIPT] Error: VLCKit path is required"
    exit 1
fi

if [ -z $DIR ]; then
    echo "[$SCRIPT] Error: Output path is required"
    exit 2
fi

if [ -z $TYPE ]; then
    echo "[$SCRIPT] Error: OS type is required"
    exit 2
fi

LIBEXT=".a"

LIBS=`cat $1/MobileVLCKit/vlc-plugins-iPhone.xcconfig`
LIBS=${LIBS/VLC_PLUGINS_LDFLAGS=/}

LIBS=`echo $LIBS | sed -e 's/\$([^()]*)//g'`
LIBS=`echo $LIBS | sed -e 's/\/MobileVLCKit\/ImportedSources\/vlc\/install-ios-iPhone\///g'`
LIBS=`echo $LIBS | sed -e 's/\.a//g'`

# Remove non universal plugins
LIBS=`echo $LIBS | sed -e 's/ plugins\/libyuv_rgb_neon_plugin plugins\/libchroma_yuv_neon_plugin//g'`

LIBS="$LIBS core/libcompat core/libvlc core/libvlccore"

if [ ! -d "$DIR" ]; then
    echo "[$SCRIPT] Creating $DIR"
    mkdir -p $DIR
fi
if [ ! -d "$DIR/contrib" ]; then
    mkdir $DIR/contrib
fi
if [ ! -d "$DIR/core" ]; then
    mkdir $DIR/core
fi
if [ ! -d "$DIR/plugins" ]; then
    mkdir $DIR/plugins
fi

OUT=libvlc

if [ "$TYPE" == "SIMULATOR" ]; then
    ARCHS="i386 x86_64"
else
    ARCHS="armv7 armv7s arm64"
fi

for arch in $ARCHS
do
    CURRLIBS=$LIBS
    if [ "$arch" == "armv7" ] || [ "$arch" == "armv7s" ] ; then
        CURRLIBS="${CURRLIBS} plugins/libyuv_rgb_neon_plugin plugins/libchroma_yuv_neon_plugin"
    fi

    for lib in $CURRLIBS
    do
        lipo -extract $arch $INPATH/$lib$LIBEXT -o $DIR/$lib-$arch$LIBEXT
    done
    INLIBS=`eval echo $DIR/\{${CURRLIBS// /,}\}-$arch$LIBEXT`
    libtool -static -o $DIR/$OUT-$arch$LIBEXT $INLIBS
done

OUTLIBS=`eval echo $DIR/$OUT-\{${ARCHS// /,}\}$LIBEXT`
lipo -create $OUTLIBS -o $DIR/$OUT$LIBEXT
