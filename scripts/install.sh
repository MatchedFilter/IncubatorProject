#!/bin/bash
./configure.sh
./build.sh
cd ..
cmake --install BuildDir
cd scripts