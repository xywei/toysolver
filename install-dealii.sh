#!/bin/sh

wget -nc https://github.com/dealii/dealii/releases/download/v8.3.0/dealii-8.3.0.tar.gz 
tar -xf dealii-8.3.0.tar.gz
mkdir -p dealii-build
cd dealii-build
cmake --DCMAKE_INSTALL_PREFIX=../dealii-installed ../dealii-8.3.0
make
make install
