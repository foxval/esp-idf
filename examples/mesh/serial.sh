#!/bin/bash

if [ -z "$1" ]; then
    echo "----------------------"
    echo "input ttyUSB index"
    read input
    index=$input
else
    index=$1
fi


rm -rf  $index.md

minicom -D /dev/ttyUSB$index -c on -C $index.md


