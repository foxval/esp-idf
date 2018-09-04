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

def fpga_connect_attempt(self, mode='ignored', esp32r0_delay=False):
    self._port.setDTR(True)   # IO0 High
    self._port.setRTS(True)   # EN=LOW, chip in reset
    time.sleep(0.1)
    self._port.setRTS(False)  # chip out of reset

    print("Waiting for FPGA reset to complete...")
    p = self._port
    saved_timeout = self._port.timeout

    p.timeout=4
    for max_lines in range(20):
        l = p.readline().strip()
        if len(l):
            print(l)
        if b"boot:" in l:  # probably a boot mode line
            if b"DOWNLOAD_BOOT" in l:
                # correct mode!
                for tries in range(10):
                    try:
                        time.sleep(0.25)
                        self.flush_input()
                        self._port.flushOutput()
                        self.sync()
                        print("Synced with FPGA")
                        return
                    except esptool.FatalError as e:
                        pass
                raise esptool.FatalError("Failed to sync")
            else:
                raise esptool.FatalError("Wrong boot mode!")

esptool.ESPLoader._connect_attempt = fpga_connect_attempt
esptool.main()

