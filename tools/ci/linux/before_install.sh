#!/bin/bash
set -ev

# Setup display
export DISPLAY=:99.0
sh -e /etc/init.d/xvfb start

# Prepare build environment
mkdir dependencies
mkdir build
mkdir install

export VLCQT_VERSION=`cat VERSION`
