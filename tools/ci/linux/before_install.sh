#!/bin/bash
set -ev

# Prepare build environment
mkdir dependencies
mkdir install-qt4
mkdir install-qt5
mkdir build-qt4
mkdir build-qt5

export VLCQT_VERSION=`cat VERSION`
