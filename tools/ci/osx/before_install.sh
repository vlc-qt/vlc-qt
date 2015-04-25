#!/bin/bash
set -ev

# Prepare build environment
mkdir dependencies
mkdir install
mkdir build-release
mkdir build-debug

# Update homebrew
brew update
