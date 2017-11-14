#!/bin/bash
set -e
export IDF_PATH=$(pwd)/../../../esp-idf
echo "----------------------"
echo "PLease Check IDF_PATH"
echo "IDF_PATH"
echo $IDF_PATH
echo "---------------------"

# make bootloader
# make partition
# make clean
# make V=1
make


if [ -z "$1" ]; then
    echo "----------------------"
    echo "input ttyUSB index"
    read input
    index=$input
else
    index=$1　	
fi


#python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port /dev/ttyUSB$index erase_flash
python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port /dev/ttyUSB$index --baud 1152000 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 $(pwd)/build/bootloader/bootloader.bin 0x10000 $(pwd)/build/mesh.bin 0x8000 $(pwd)/build/partitions_singleapp.bin


