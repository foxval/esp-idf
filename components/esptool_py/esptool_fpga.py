#!/usr/bin/env python
import sys
import os.path
import time
sys.path.append(os.path.join(os.path.dirname(__file__), 'esptool'))

import esptool, serial

# Monkey-patch esptool so it can auto-reset the FPGA to flash it
#
# For Altera FPGA, needs connections to motherboard:
# - RTS connected to J14 pin #40 (pin name GPIO1_D31 in manual)
# - DTR connected to J13 pin #2 (pin name GPIO0_D0 in manual)
# - DIP switch SW4 #4 in position UP (GPIO bootstrap mode)
#
# See FPGA manual for full details.
#
# Run esptool_fpga.py the same as running esptool.py. Any --before argument is ignored, FPGA is always
# reset via serial pins
#

esptool.SYNC_TIMEOUT = 0.2

# sync a bit slower for 10M fpga images (shouldn't cause problems for faster images)
esptool.ESPLoader.ESP_ROM_BAUD = 57600

esptool.main()

