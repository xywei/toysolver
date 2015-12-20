#!/bin/sh

cd $HOME
wget -nc https://github.com/dealii/dealii/releases/download/v8.3.0/dealii-8.3.0.tar.gz
if cd dealii-8.3.0; then cd $HOME ; else tar -xf dealii-8.3.0.tar.gz; fi
mkdir -p dealii-build
cd dealii-build
cmake --DCMAKE_INSTALL_PREFIX=$HOME/dealii-installed $HOME/dealii-8.3.0
make -j2
sudo make install
