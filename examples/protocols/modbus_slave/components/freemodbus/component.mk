#
# Main component makefile.
#
# This Makefile can be left empty. By default, it will take the sources in the 
# src/ directory, compile them and link them into lib(subdirectory_name).a 
# in the build directory. This behaviour is entirely configurable,
# please read the ESP-IDF documents if you need to do this.
#
#COMPONENT_ADD_INCLUDEDIRS := . modbus/include modbus port modbus/ascii modbus/functions modbus/rtu
COMPONENT_ADD_INCLUDEDIRS := modbus/include port
COMPONENT_PRIV_INCLUDEDIRS := . modbus/include modbus port modbus/ascii modbus/functions modbus/rtu
COMPONENT_SRCDIRS := . modbus port modbus/ascii modbus/functions modbus/rtu

CXXFLAGS += -fno-rtti