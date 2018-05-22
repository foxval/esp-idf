# Modbus Slave Example

This example demonstrates using FreeModbus stack port implementation for ESP32.
It is able to read/write device parameters using Modbus protocol transport.
The parameters are prepared in Excel spreadsheet and can be used to generate 
deviceparams.h/c, lookup_tables.h/c files located in \main\mbcontroller folder. 
The first one represents device parameters storage structures, second one is the 
object dictionary to keep extended information about parameters.
To be able to communicate in RS485 network this example requires the RS485 adapters connected to UART pins as below:
RS485 example circuit schematic:
   
         VCC ---------------+                               +--------------- VCC
                            |                               |
                    +-------x-------+               +-------x-------+
         RXD <------| RO            | DIFFERENTIAL  |             RO|-----> RXD
                    |              B|---------------|B              |
         TXD ------>| DI   MAX485   |    \  /       |    MAX485   DI|<----- TXD
ESP32 WROVER KIT 1  |               |   RS-485 side |               |          ESP32 WROVER KIT 2
         RTS --+--->| DE            |    /  \       |             DE|---+       OR external master
               |    |              A|---------------|A              |   |
               +----| /RE           |    PAIR       |            /RE|---+-- RTS
                    +-------x--------+              +-------x-------+
                            |                               |
                           ---                             --- 
The FreeModbus port files located in folder .\components\freemodbus\port\ and can be corrected to 
change modbus stack parameters such as UART pins and etc (See portserial.c for serial port parametrs).