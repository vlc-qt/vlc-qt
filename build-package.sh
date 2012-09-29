#!/bin/bash
#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2012 Tadej Novak <tadej@tano.si>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library. If not, see <http://www.gnu.org/licenses/>.
#############################################################################

set -eu

TARGET=""
while getopts "ht:" OPTION
do
  case $OPTION in
      h)
          echo "Quick build system for VLC-Qt library."
          echo ""
          echo "Use -t to specify target (in targets directory)"
	  exit 0
	  ;;
      t)
	  TARGET="$OPTARG"
	  ;;
  esac
done

if [[ -z $TARGET ]]; then
    echo "Target (-t) not specified"
    exit 1
fi


if [ -f targets/${TARGET}.sh ]; then
    source targets/${TARGET}.sh
else
    echo "Target $TARGET not supported"
    exit 1
fi
