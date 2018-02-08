#!/bin/bash
#set -e

export IDF_PATH=$(pwd)/../../../esp-idf
echo "----------------------"
echo "PLease Check IDF_PATH"
echo "IDF_PATH"
echo $IDF_PATH
echo "---------------------"

rm -rf  $(pwd)/mlog

#make clean
make -j8 

echo "pkill minicom"
pkill minicom
sleep 3

dw_res_array=()
dev_no=$1
if [ "$dev_no" == "" ];then
	dev_no=1
fi
loop_end=$[ $dev_no*2-1]
echo "========================"
echo "    device count: $dev_no"
echo "========================"
for i in $(seq 1 2 $loop_end )
do  
{
   { 
   python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port /dev/ttyUSB$i erase_flash 
   python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port /dev/ttyUSB$i --baud 1152000 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 $(pwd)/build/bootloader/bootloader.bin 0x10000 $(pwd)/build/mesh.bin 0x8000 $(pwd)/build/partitions_singleapp.bin 
	
	}>/dev/null
}   &
done
wait

echo "========================"
echo "    open serial port    "
echo "========================"

mkdir $(pwd)/mlog
for i in $(seq 1 2 $loop_end )
do 
	#echo "open ttyUSB$i"
	{ a=$(python  $IDF_PATH/components/esptool_py/esptool/esptool.py -b 115200 -p /dev/ttyUSB$i read_mac) b=${a##*MAC:}
	#echo $b
	c=${b:1:17}
	#echo MAC:$c

	x=$[ $[ $i%4-1 ] / 2 * 2000]
	y=$[10+$i/4*2000]
	gnome-terminal  -t $i --geometry 85x20+$x+$y -x minicom -D /dev/ttyUSB$i -c on -C mlog/[$i]--${c}.md
} &
done

