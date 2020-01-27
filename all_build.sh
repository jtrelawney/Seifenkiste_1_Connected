#!/bin/bash

#echo "$1"
if [ "$1" == "clear_all" ]; then
    echo "deleting build directory"
    rm -r ./build
    mkdir build
    echo "deleting pc_main.exe"
    rm pc_main.exe
    echo "deleting rpi4.exe"
    rm rpi4.exe
fi

cd build
cmake ..
make -j4

if [ "$2" == "1" ]; then
    echo "run pc"
    ../pc_main.exe
fi

if [ "$2" == "2" ]; then
    echo "run rpi"
    ../dirs/bin/rpi4_main.exe
fi

if [ "$2" == "3" ]; then
    echo "run both"
    cd ../dirs/bin
    ./pc_main.exe &
    sleep 1
    pwd
    ./rpi4_main.exe
fi
