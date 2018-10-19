# If any of Modbus master option is selected in KConfig then compile master code else slave
ifneq ($(filter y,$(CONFIG_MB_SERIAL_MASTER_RTU_ENABLED) $(CONFIG_MB_SERIAL_MASTER_ASCII_ENABLED)),)
COMPONENT_ADD_INCLUDEDIRS := serial_master/modbus/include serial_master/modbus_controller common
COMPONENT_PRIV_INCLUDEDIRS := . serial_master/modbus serial_master/port serial_master/modbus/ascii serial_master/modbus/functions serial_master/modbus/rtu serial_master/modbus/include 
COMPONENT_SRCDIRS := serial_master/modbus serial_master/port serial_master/modbus/ascii serial_master/modbus/functions serial_master/modbus/rtu serial_master/modbus_controller
else
COMPONENT_ADD_INCLUDEDIRS := serial_slave/modbus/include serial_slave/modbus_controller common
COMPONENT_PRIV_INCLUDEDIRS := serial_slave/modbus serial_slave/port serial_slave/modbus/ascii serial_slave/modbus/functions serial_slave/modbus/rtu serial_slave/modbus/include 
COMPONENT_SRCDIRS := serial_slave/modbus serial_slave/port serial_slave/modbus/ascii serial_slave/modbus/functions serial_slave/modbus/rtu serial_slave/modbus_controller
endif