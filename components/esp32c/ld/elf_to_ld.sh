#!/bin/bash

echo '/*'
echo 'ESP32C ROM address table'
echo 'Generated for ROM with MD5sum:'
md5sum $1
echo '*/'
xtensa-esp32-elf-nm $1 | grep '[0-9a-f] [TBRD]' | while read adr ttp nm; do 
	if ! echo "$nm" | grep -q -e '^_bss' -e '_heap'; then
                if [ "$nm" != "_data_start" -a "$nm" != "_data_end" ]; then
                        echo "PROVIDE ( $nm = 0x$adr );";
                fi
	fi
done
