#ifndef _DEVICE_PARAMS
#define _DEVICE_PARAMS

#define GET_PARAMETER_ADDRESS(parInfo) ((uint8_t*)((uint8_t*)&holdingRegParams + (uint32_t)parInfo->paramOffset))
#define A12_ARR_SIZE 12
#define A24_ARR_SIZE 24

#define PAR_HELPER(fmt, ...) printf(fmt "\n%s", __VA_ARGS__)
#define PAR(...) PAR_HELPER(__VA_ARGS__, "")

#define PAR_PREF(...) (*(&(holdingRegParams.##__VA_ARGS__)))
#define DEVICE_PAR(param) &(holdingRegParams.##param)
#define DEVICE_PAR_VOID(param) ((void*)&(holdingRegParams.##param))

#pragma pack(push, 1)
typedef struct
{
    // Parameter: Coil 0 : Coil0
    uint8_t coil0:1;
    // Parameter: Coil 1 : Coil1
    uint8_t coil1:1;
    // Parameter: Coil 2 : Coil2
    uint8_t coil2:1;
    // Parameter: Coil 3 : Coil3
    uint8_t coil3:1;
    // Parameter: Coil 4 : Coil4
    uint8_t coil4:1;
    // Parameter: Coil 5 : Coil5
    uint8_t coil5:1;
    // Parameter: Coil 6 : Coil6
    uint8_t coil6:1;
    // Parameter: Coil 7 : Coil7
    uint8_t coil7:1;
    // Coils port 1
    uint8_t coilPort1:8;

} tCoilRegParams;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    // Parameter: Data channel 0 : DataChan0 : NV Address: 0
    float dataChan0;
    // Parameter: Data channel 1 : DataChan1 : NV Address: 0
    float dataChan1;
    // Parameter: Data channel 2 : DataChan2 : NV Address: 0
    float dataChan2;
    // Parameter: Data channel 3 : DataChan2 : NV Address: 0
    float dataChan3;
} tInputRegParams;
#pragma pack(pop)


// This is script auto generated structure. See register map for more information.
#pragma pack(push, 1)
typedef struct
{
    // Parameter: Data channel 0 : DataChan0 : NV Address: 0
    float dataChan0;
    // Parameter: Data channel 1 : DataChan1 : NV Address: 0
    float dataChan1;
    // Parameter: Data channel 2 : DataChan2 : NV Address: 0
    float dataChan2;
    // Parameter: Data channel 3 : DataChan3 : NV Address: 0
    float dataChan3;
    // Parameter: Protocol version  : protocolVersion : NV Address: 0
    uint16_t protocolVers;
    // Parameter: Hardware version  : hardwareVersion : NV Address: 2
    uint16_t hardwareVers;
    // Parameter: Software Version : softwareVersion : NV Address: 4
    uint16_t softwareVers;
    // Parameter: Software Revision : softwareRevision : NV Address: 6
    uint16_t softwareRev;
    // Parameter: Device Type : deviceType : NV Address: 8
    uint16_t deviceType;
    // Parameter: Modbus Network Address : modbusAddress : NV Address: 10
    uint16_t modbusAddress;
    // Parameter: Modbus Baudrate : modbusBaud : NV Address: 10
    uint16_t modbusBaud;
    // Parameter: Modbus parity  : modbusParity : NV Address: 10
    uint16_t modbusParity;
    // Parameter: Modbus stopbit  : mbStopBits : NV Address: 10
    uint16_t mbStopBits;
    // Parameter: Brace control  : mbBraceCtrl : NV Address: 10
    uint16_t mbBraceCtrl;
    // Parameter: Serial number  : serialNumber : NV Address: 12
    uint32_t serialNumber;
    // Parameter: Up time  : uptime : NV Address: 16
    uint32_t upTime;
    // Parameter: Device state  : deviceState : NV Address: 16
    uint16_t deviceState;
    // Parameter: Test Float0  : TestFloat0 : NV Address: 20
    float testFloat0;
    // Parameter: Test Float1  : TestFloat1 : NV Address: 24
    float testFloat1;
    // Parameter: Test Float2  : TestFloat2 : NV Address: 28
    float testFloat2;
    // Parameter: Test Float3  : TestFloat3 : NV Address: 32
    float testFloat3;
    // Parameter: Test String  : StringTest : NV Address: 32
    uint8_t stringTest[A24_ARR_SIZE];
} tHoldingRegParams;
#pragma pack(pop)

extern const uint16_t g_numLookupRegisters;
extern tHoldingRegParams holdingRegParams;
extern tInputRegParams inputRegParams;
extern tCoilRegParams coilRegParams;

#endif // !defined(_DEVICE_PARAMS)
