#!/bin/bash
set -e
export IDF_PATH=$(pwd)/../../../../esp-idf
echo "----------------------"
echo "PLease Check IDF_PATH"
echo "IDF_PATH"
echo $IDF_PATH
echo "---------------------"


touch $IDF_PATH/components/esp32/lib/libmesh.a
touch $IDF_PATH/components/esp32/lib/libnet80211.a
touch $IDF_PATH/components/esp32/lib/libpp.a

# make bootloader
# make partition
# make clean
# make V=1
make

#idf 0.9
#sudo python $(pwd)/../../../../esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port $dev --baud $baud write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 $(pwd)/build/#bootloader/bootloader.bin 0x10000 $(pwd)/build/mesh-demo.bin 0x4000 $(pwd)/build/partitions_singleapp.bin

#idf 2.0
#sudo python /home/qiyuexia/Working/mesh/esp32/master/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port $dev --baud 921600 --before default_reset --after hard_reset write_flash -z --#flash_mode dio --flash_freq 40m --flash_size detect 0x1000 /home/qiyuexia/Working/mesh/esp32/master/esp-idf/examples/mesh/bfc_demo/build/bootloader/bootloader.bin 0x10000 /home/qiyuexia/Working/mesh/#esp32/master/esp-idf/examples/mesh/bfc_demo/build/bfc_demo.bin 0x8000 /home/qiyuexia/Working/mesh/esp32/master/esp-idf/examples/mesh/bfc_demo/build/partitions_singleapp.bin

baud=1152000 
for i in 1 3 5 7 9 11 13 15 17 19 21 23
do 
    dev=/dev/ttyUSB$i
    echo port:$dev
python $(pwd)/../../../../esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port $dev --baud $baud --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 $(pwd)/build/bootloader/bootloader.bin 0x10000 $(pwd)/build/bfc_demo.bin 0x8000 $(pwd)/build/partitions_singleapp.bin
done


