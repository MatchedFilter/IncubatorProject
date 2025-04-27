#!/bin/bash
chmod +x build.sh install.sh clean.sh
cd ..
cmake -S . -B BuildDir -G"Ninja" -DCMAKE_BUILD_TYPE=Debug
cd scripts

