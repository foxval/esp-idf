# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

if(CONFIG_MB_MASTER_RTU_ENABLED OR CONFIG_MB_MASTER_ASCII_ENABLED)
    set(COMPONENT_SRCS "serial_master/modbus/ascii/mbascii.c"
                   "serial_master/modbus/rtu/mbcrc.c"
                   "serial_master/modbus/functions/mbfunccoils.c"
                   "serial_master/modbus/functions/mbfuncdiag.c"
                   "serial_master/modbus/functions/mbfuncdisc.c"
                   "serial_master/modbus/functions/mbfuncholding.c"
                   "serial_master/modbus/functions/mbfuncinput.c"
                   "serial_master/modbus/functions/mbfuncother.c"
                   "serial_master/modbus/rtu/mbrtu.c"
                   "serial_master/modbus/tcp/mbtcp.c"
                   "serial_master/modbus/functions/mbutils.c"
                   "serial_master/port/portevent.c"
                   "serial_master/port/portother.c"
                   "serial_master/port/portserial.c"
                   "serial_master/port/porttimer.c"
                   "serial_master/modbus_controller/mbcontroller.c"
                   "serial_master/modbus/mb.c")
    
    set(COMPONENT_ADD_INCLUDEDIRS serial_master/modbus/include serial_master/modbus_controller)
    set(COMPONENT_PRIV_INCLUDEDIRS serial_master/port serial_master/modbus/ascii serial_master/modbus/functions serial_master/modbus/rtu serial_master/modbus/include)
else()
    set(COMPONENT_SRCS "serial_slave/modbus/ascii/mbascii.c"
                   "serial_slave/modbus/rtu/mbcrc.c"
                   "serial_slave/modbus/functions/mbfunccoils.c"
                   "serial_slave/modbus/functions/mbfuncdiag.c"
                   "serial_slave/modbus/functions/mbfuncdisc.c"
                   "serial_slave/modbus/functions/mbfuncholding.c"
                   "serial_slave/modbus/functions/mbfuncinput.c"
                   "serial_slave/modbus/functions/mbfuncother.c"
                   "serial_slave/modbus/rtu/mbrtu.c"
                   "serial_slave/modbus/tcp/mbtcp.c"
                   "serial_slave/modbus/functions/mbutils.c"
                   "serial_slave/port/portevent.c"
                   "serial_slave/port/portother.c"
                   "serial_slave/port/portserial.c"
                   "serial_slave/port/porttimer.c"
                   "serial_slave/modbus_controller/mbcontroller.c"
                   "serial_slave/modbus/mb.c")
    
    set(COMPONENT_ADD_INCLUDEDIRS serial_slave/modbus/include serial_slave/modbus_controller)
    set(COMPONENT_PRIV_INCLUDEDIRS serial_slave/port serial_slave/modbus/ascii serial_slave/modbus/functions serial_slave/modbus/rtu serial_slave/modbus/include)
endif()

set(COMPONENT_REQUIRES "driver")

register_component()
