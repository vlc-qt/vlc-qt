#!/bin/bash
set -ev

# Prepare build environment
mkdir dependencies
mkdir install
mkdir install/artifacts
mkdir build

export VLCQT_VERSION=`cat VERSION`

# Update homebrew
brew update
