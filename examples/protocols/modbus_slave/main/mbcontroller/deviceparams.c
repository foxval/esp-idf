 /*=====================================================================================
 * Filename: deviceparams.c
 *=====================================================================================
 * Description:
 *   C file to define parameter storage instances
 *====================================================================================*/
#include <stdint.h>
#include "lookup_tables.h"

// This is main storage for device parameters packed by 1 byte
tHoldingRegParams holdingRegParams = { 0 };

tInputRegParams inputRegParams = { 0 };

tCoilRegParams coilRegParams = { 0 };

