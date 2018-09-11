# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(COMPONENT_SRCDIRS modbus port modbus/ascii modbus/functions modbus/rtu modbus_controller)
set(COMPONENT_ADD_INCLUDEDIRS modbus/include modbus_controller)
set(COMPONENT_PRIV_INCLUDEDIRS . modbus port modbus/ascii modbus/functions modbus/rtu modbus/include)
set(COMPONENT_REQUIRES "driver")

register_component()
