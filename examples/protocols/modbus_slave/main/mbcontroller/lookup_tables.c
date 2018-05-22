 /*=====================================================================================
 * Filename: lookup_tables.c
 *=====================================================================================
 * Description:
 *   C file for the Modbus registers and coil lookup tables. These tables map
 *   the registers/coils from Modbus to the appropriate location.
 *   It also defines attributes such as type and protection.
 *====================================================================================*/
#include <stdint.h>
#include "lookup_tables.h"

#define mbRegRwCheckFunc NULL       // Leave write check function blank for now
#define OFFSET(field) ((uint16_t)offsetof(tHoldingRegParams, field))
#define STR(fieldname) ((const char*)( fieldname ))

// Example Data(Object) Dictionary for Modbus parameters (is generated automatically by script)
const tLookupRegisters g_stLookupRegisters[] =
{
    // {Par Offset, NV Offset, Check Func, Parameter Offset, Data Type, Data Size, Work Mode Access | Service Mode Access | Write Protect}
    // Parameter: Data channel 0 : DataChan0
    {0, 0, mbRegRwCheckFunc,  STR("dataChan0"), OFFSET(dataChan0), LKUP_TYPE_FLOAT, 4, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Data channel 1 : dataChan1
    {2, 0, mbRegRwCheckFunc,  STR("dataChan1"), OFFSET(dataChan1), LKUP_TYPE_FLOAT, 4, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Data channel 2 : dataChan2
    {4, 0, mbRegRwCheckFunc,  STR("dataChan2"), OFFSET(dataChan2), LKUP_TYPE_FLOAT, 4, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Data channel 3 : dataChan3
    {6, 0, mbRegRwCheckFunc,  STR("dataChan3"), OFFSET(dataChan3), LKUP_TYPE_FLOAT, 4, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Protocol version  : protocolVers
    {16384, 0, mbRegRwCheckFunc,  STR("protocolVers"), OFFSET(protocolVers), LKUP_TYPE_U16, 2, LKUP_ACCESS_TYPE_STATIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Hardware version  : hardwareVers
    {16385, 2, mbRegRwCheckFunc,  STR("hardwareVers"), OFFSET(hardwareVers), LKUP_TYPE_U16, 2, LKUP_ACCESS_TYPE_STATIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Software Version : softwareVersion
    {16386, 4, mbRegRwCheckFunc,  STR("softwareVers"), OFFSET(softwareVers), LKUP_TYPE_U16, 2, LKUP_ACCESS_TYPE_STATIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Software Revision : softwareRev
    {16387, 6, mbRegRwCheckFunc,  STR("softwareRev"), OFFSET(softwareRev), LKUP_TYPE_U16, 2, LKUP_ACCESS_TYPE_STATIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Device Type : deviceType
    {16388, 8, mbRegRwCheckFunc,  STR("deviceType"), OFFSET(deviceType), LKUP_TYPE_U16, 2, LKUP_ACCESS_TYPE_STATIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Modbus Network Address : modbusAddress
    {16389, 10, mbRegRwCheckFunc,  STR("modbusAddress"), OFFSET(modbusAddress), LKUP_TYPE_U16, 2, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Modbus Baudrate : modbusBaud
    {16390, 10, mbRegRwCheckFunc,  STR("modbusBaud"), OFFSET(modbusBaud), LKUP_TYPE_U16, 2, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Modbus parity  : modbusParity
    {16391, 10, mbRegRwCheckFunc,  STR("modbusParity"), OFFSET(modbusParity), LKUP_TYPE_U16, 2, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Modbus stopbit  : mbStopBits
    {16392, 10, mbRegRwCheckFunc,  STR("mbStopBits"), OFFSET(mbStopBits), LKUP_TYPE_U16, 2, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Brace control  : mbBraceCtrl
    {16393, 10, mbRegRwCheckFunc,  STR("mbBraceCtrl"), OFFSET(mbBraceCtrl), LKUP_TYPE_U16, 2, LKUP_ACCESS_TYPE_STATIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Serial number  : serialNumber
    {16395, 12, mbRegRwCheckFunc,  STR("serialNumber"), OFFSET(serialNumber), LKUP_TYPE_U32, 4, LKUP_ACCESS_TYPE_STATIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_RW | LKUP_ACCESS_NO_WRITE_PROTECT},
    // Parameter: Up time  : uptime
    {16397, 16, mbRegRwCheckFunc,  STR("upTime"), OFFSET(upTime), LKUP_TYPE_U32, 4, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Device state  : deviceState
    {16399, 16, mbRegRwCheckFunc,  STR("deviceState"), OFFSET(deviceState), LKUP_TYPE_U16, 2, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Test Float 0 : testFloat0
    {16401, 0, mbRegRwCheckFunc,  STR("testFloat0"), OFFSET(testFloat0), LKUP_TYPE_FLOAT, 4, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Test Float 1 : testFloat1
    {16405, 0, mbRegRwCheckFunc,  STR("testFloat1"), OFFSET(testFloat1), LKUP_TYPE_FLOAT, 4, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Test Float 2 : testFloat2
    {16409, 0, mbRegRwCheckFunc,  STR("testFloat2"), OFFSET(testFloat2), LKUP_TYPE_FLOAT, 4, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: Test Float 3 : testFloat3
    {16413, 0, mbRegRwCheckFunc,  STR("testFloat3"), OFFSET(testFloat3), LKUP_TYPE_FLOAT, 4, LKUP_ACCESS_TYPE_DYNAMIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_WRITE_PROTECT},
    // Parameter: String Test : stringTest
    {16415, 0, mbRegRwCheckFunc,  STR("stringTest"), OFFSET(stringTest), LKUP_TYPE_ASCII, 24, LKUP_ACCESS_TYPE_STATIC | LKUP_ACCESS_WORK_R | LKUP_ACCESS_SERV_R | LKUP_ACCESS_NO_WRITE_PROTECT},
};

const uint16_t g_numLookupRegisters = (sizeof(g_stLookupRegisters)/sizeof(g_stLookupRegisters[0]));


