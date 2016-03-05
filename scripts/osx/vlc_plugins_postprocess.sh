#!/bin/bash
#
# Usage:
#   osx_vlc_plugins_postprocess.sh
#
# Use install_name_tool(1) to update plugins in current directory so that the
# dynamic loader will look for VLC libraries in specific locations, and in a
# specific order.
#
# This script:
# - Changes the install names of the libvlc and libvlccore libraries so that
#   they refer to @../../

SCRIPT=$(basename "$0")

doo(){
  echo "[$SCRIPT] $@"
  "$@"
}

# change_install_name oldname newname file.dylib
change_install_name() {
  OLD="$1"
  NEW="$2"
  FILE="$3"

  OTOOL_OUT=$(otool -l "$FILE")
  echo "$OTOOL_OUT" | grep -q "$OLD"
  if [ ! $? -eq 0 ] ; then
    # Old name not present
    echo "$OTOOL_OUT" | grep -q "$NEW"
    if [ ! $? -eq 0 ] ; then
      # New name not present => error
      echo "[$SCRIPT] Error: no reference to '$OLD' found in '$FILE'"
      exit 1
    fi
  else
    doo install_name_tool -change "$OLD" "$NEW" "$FILE"
  fi
}

##

echo "[$SCRIPT] # Processing: '`pwd`'"

for DYLIB in *.dylib;
do
  LIBVLCCORE=$(otool -L "$DYLIB" | grep '\(/libvlccore\..[0-9]*\.dylib\)' -o)
  LPLIBVLCCORE=$(otool -L "$DYLIB" | grep '\(loader_path/.*lib/libvlccore\..[0-9]*\.dylib\)' -o)
  if otool -L "$DYLIB" | grep '\(loader_path/.*lib/libvlccore\..[0-9]*\.dylib\)' -o; then
    change_install_name @$LPLIBVLCCORE @loader_path/../..$LIBVLCCORE "$DYLIB"
  fi
done

echo "[$SCRIPT] # '`pwd`' is up-to-date"
