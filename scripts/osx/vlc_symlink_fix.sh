#!/bin/bash
#
# Usage:
#   osx_vlc_symlink_fix.sh <dir>
#
# Fix symlinks provided by default package
#

SCRIPT=$(basename "$0")
DIR="$1"

if [ ! -e "$DIR" ] ; then
  echo "[$SCRIPT] Error: directory not found ('$1')" >&2
  exit 1
fi

echo "[$SCRIPT] # Processing: '$DIR'"

pushd $DIR

LIBVLC=$(ls | grep '\(libvlc\..[0-9]*\.dylib\)' -o)
LIBVLCCORE=$(ls| grep '\(libvlccore\..[0-9]*\.dylib\)' -o)

ln -sf $LIBVLC libvlc.dylib
ln -sf $LIBVLCCORE libvlccore.dylib

echo "[$SCRIPT] # Symlinks fixed in '$DIR'"

popd $DIR
