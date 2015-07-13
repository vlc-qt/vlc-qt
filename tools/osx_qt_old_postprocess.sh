#!/bin/bash
#
# Usage:
#   osx_qt_old_postprocess.sh <dylib>
#
# Use install_name_tool(1) to update <dylib> so that the dynamic loader will
# look for Qt libraries in Frameworks
#

SCRIPT=$(basename "$0")
DYLIB="$1"

if [ ! -e "$DYLIB" ] ; then
  echo "[$SCRIPT] Error: file not found ('$1')" >&2
  exit 1
fi

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

echo "[$SCRIPT] # Processing: '$DYLIB'"

QTCOREID=$(otool -L "$DYLIB" | grep '\(/QtCore.framework/Versions/5/QtCore\)' -o)
QTCORE=$(otool -L "$DYLIB" | grep '\(.*/QtCore.framework/Versions/5/QtCore\)' -o)

QTGUIID=$(otool -L "$DYLIB" | grep '\(/QtGui.framework/Versions/5/QtGui\)' -o)
QTGUI=$(otool -L "$DYLIB" | grep '\(.*/QtGui.framework/Versions/5/QtGui\)' -o)

QTNETWORKID=$(otool -L "$DYLIB" | grep '\(/QtNetwork.framework/Versions/5/QtNetwork\)' -o)
QTNETWORK=$(otool -L "$DYLIB" | grep '\(.*/QtNetwork.framework/Versions/5/QtNetwork\)' -o)

QTQUICKID=$(otool -L "$DYLIB" | grep '\(/QtQuick.framework/Versions/5/QtQuick\)' -o)
QTQUICK=$(otool -L "$DYLIB" | grep '\(.*/QtQuick.framework/Versions/5/QtQuick\)' -o)

QTQMLID=$(otool -L "$DYLIB" | grep '\(/QtQml.framework/Versions/5/QtQml\)' -o)
QTQML=$(otool -L "$DYLIB" | grep '\(.*/QtQml.framework/Versions/5/QtQml\)' -o)

QTWIDGETSID=$(otool -L "$DYLIB" | grep '\(/QtWidgets.framework/Versions/5/QtWidgets\)' -o)
QTWIDGETS=$(otool -L "$DYLIB" | grep '\(.*/QtWidgets.framework/Versions/5/QtWidgets\)' -o)

if [ -n "$QTCORE" ]; then
  change_install_name $QTCORE @executable_path/../Frameworks$QTCOREID "$DYLIB"
fi

if [ -n "$QTGUI" ]; then
  change_install_name $QTGUI @executable_path/../Frameworks$QTGUIID "$DYLIB"
fi

if [ -n "$QTNETWORK" ]; then
  change_install_name $QTNETWORK @executable_path/../Frameworks$QTNETWORKID "$DYLIB"
fi

if [ -n "$QTQUICK" ]; then
  change_install_name $QTQUICK @executable_path/../Frameworks$QTQUICKID "$DYLIB"
fi

if [ -n "$QTQML" ]; then
  change_install_name $QTQML @executable_path/../Frameworks$QTQMLID "$DYLIB"
fi

if [ -n "$QTWIDGETS" ]; then
  change_install_name $QTWIDGETS @executable_path/../Frameworks$QTWIDGETSID "$DYLIB"
fi

echo "[$SCRIPT] # '$DYLIB' is up-to-date"
