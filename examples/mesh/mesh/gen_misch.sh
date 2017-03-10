#!/bin/bash
set -e
export IDF_PATH=$(pwd)/../../../../esp-idf
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

echo "----------------------"
echo "input ttyUSB index"
read input
baud=921600
if [ -z "$input" ]; then
    dev=/dev/ttyUSB0
else
    if [ "$input" -gt 9 ]; then
        baud=115200
    fi
    dev=/dev/ttyUSB$input
fi
echo "you select device:"
echo $dev
echo $baud
echo "----------------------"

#download run image to dev-board
#sudo python /home/share/alen/esp-idf/examples/mesh/../../../esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port $dev --baud $baud write_flash -z --flash_mode dio --flash_freq 40m --#flash_size 2MB 0x1000 /home/share/alen/esp-idf/examples/mesh/build/bootloader/bootloader.bin 0x10000 /home/share/alen/esp-idf/examples/mesh/build/mesh-demo.bin 0x4000 /home/share/alen/esp-idf/examples/#mesh/build/partitions_singleapp.bin

#idf 0.9
#sudo python $(pwd)/../../../../esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port $dev --baud $baud write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 $(pwd)/build/#bootloader/bootloader.bin 0x10000 $(pwd)/build/mesh-demo.bin 0x4000 $(pwd)/build/partitions_singleapp.bin

sudo python $(pwd)/../../../../esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port $dev --baud $baud --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 $(pwd)/../../../../esp-idf/examples/mesh/mesh/build/bootloader/bootloader.bin 0x10000 $(pwd)/../../../../esp-idf/examples/mesh/mesh/build/mesh-demo.bin 0x8000 $(pwd)/../../../../esp-idf/examples/mesh/mesh/build/partitions_singleapp.bin

