#!/bin/bash
set -ev

# Setup display
export DISPLAY=:99.0
sh -e /etc/init.d/xvfb start

# Install Ubuntu packages
sudo add-apt-repository ppa:ntadej/tano -y
sudo apt-get update -qq
sudo apt-get install libvlc-dev libvlccore-dev vlc p7zip-full lcov -y

# Install Qt
if [ $QT_VERSION -eq 5 ]
then
    sudo apt-get install qtbase5-dev qtdeclarative5-dev -y
else
    sudo apt-get install libqt4-dev -y
fi

# Prepare build environment
mkdir dependencies
mkdir build
mkdir install

export VLCQT_VERSION=`cat VERSION`
