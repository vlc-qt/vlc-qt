#!/bin/bash
set -ev

# Prepare build environment
mkdir dependencies
mkdir build
mkdir build-static
mkdir install
mkdir install-static

export VLCQT_VERSION=`cat VERSION`

# Update homebrew
brew update
