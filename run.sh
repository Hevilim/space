#!/bin/bash

[ -d build ] || mkdir build
cd build
make clean 
make
./space
