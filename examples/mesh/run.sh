#!/bin/bash
#set -e

export IDF_PATH=$(pwd)/../../../esp-idf
echo "======================"
echo "check IDF_PATH:" $IDF_PATH
echo "======================"

#make clean
make -j8

echo "======================"
echo "pkill minicom"
echo "======================"
pkill minicom
sleep 3

dev_num=$1
if [ "$dev_num" == "" ]; then
    dev_num=1
fi
loop_end=$[ $dev_num*2-1]
echo "======================"
echo "device number: $dev_num"
echo "erase flash"
echo "downloading ..."
echo "======================"
for i in $(seq 1 2 $loop_end )
do {
    { python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port /dev/ttyUSB$i erase_flash
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port /dev/ttyUSB$i --baud 1152000 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 $(pwd)/build/bootloader/bootloader.bin 0x10000 $(pwd)/build/mesh.bin 0x8000 $(pwd)/build/partitions_singleapp.bin 
    } >/dev/null
} &
done
wait

echo "======================"
echo "open serial port"
echo "======================"
rm -rf  $(pwd)/mlog
mkdir $(pwd)/mlog
for i in $(seq 1 2 $loop_end )
do {
    a=$(python  $IDF_PATH/components/esptool_py/esptool/esptool.py -b 115200 -p /dev/ttyUSB$i read_mac)
    b=${a##*MAC:}
    c=${b:1:17}
    x=$[ $[ $i%4-1 ] / 2 * 800]
    y=$[10+$i/4 * 800]
    gnome-terminal  -t $i --geometry 85x20+$x+$y -x minicom -D /dev/ttyUSB$i -c on -C mlog/[$i]--${c}.md
} &
done
