#!/bin/bash
set -ev

# Setup display
export DISPLAY=:99.0
sh -e /etc/init.d/xvfb start

# Prepare build environment
mkdir dependencies
mkdir install-qt4
mkdir install-qt5
mkdir build-qt4
mkdir build-qt5

export VLCQT_VERSION=`cat VERSION`
