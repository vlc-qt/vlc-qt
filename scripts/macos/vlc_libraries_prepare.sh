#!/bin/bash
#
# Usage:
#   vlc_libraries_prepare.sh <vlc-dir> <output-dir>
#
# Copies required VLC libraries and plugins to temporary folder in build
# directory and processes them
#

SCRIPT=$(basename "$0")
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd`
popd > /dev/null

DIR="$1"
OUTPUT="$2"
PROCESSED="$OUTPUT/libvlc-processed"

if [ -z $DIR ]; then
    echo "[$SCRIPT] Error: VLC path is required"
    exit 1
fi

if [ -z $OUTPUT ]; then
    echo "[$SCRIPT] Error: Output path is required"
    exit 2
fi

echo $1
echo $2

if [ ! -d "$OUTPUT" ]; then
    echo "[$SCRIPT] Creating $OUTPUT"
    mkdir -p $OUTPUT
fi

echo "[$SCRIPT] Copying libraries"
if [ ! -d $PROCESSED ]; then
    mkdir $PROCESSED
fi

cp $DIR/lib/*.*.dylib $PROCESSED/

echo "[$SCRIPT] Fixing rpaths and symlinks"
for f in $PROCESSED/*.*.dylib
do
    $SCRIPTPATH/vlc_rpath_fix.sh $f
done
$SCRIPTPATH/vlc_symlink_fix.sh $PROCESSED

echo "[$SCRIPT] Copying plugins"
if [ ! -d $PROCESSED/vlc/plugins ]; then
    mkdir -p $PROCESSED/vlc/plugins
fi
cp $DIR/plugins/* $PROCESSED/vlc/plugins
for f in $PROCESSED/vlc/plugins/*.dylib
do
	$SCRIPTPATH/vlc_rpath_fix.sh $f
done
