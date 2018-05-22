///////////////////////////////////////////////////////////
//  cNvManager.h
//  Implementation of the Class cNvManager
///////////////////////////////////////////////////////////

#if !defined(_CNVMANAGER)
#define _CNVMANAGER

#include "lookup_tables.h"  // for device parameter descriptions
#include <stdint.h>         // for standard int types definition
#include <stddef.h>         // for NULL and std defines
#include <string.h>         // for memset
#include "deviceparams.h"   // for device parameters structure
#include "assert.h"         // for assert
#include "nvs.h"            // for NV storage access
#include "nvs_flash.h"

#define MB_NVS_NAMESPACE    (const char*)("MB_NAMESPACE")
#define MB_PAR_MAX_SIZE     (24) // ASCII24 size

#define INIT_PAR(param, data) do { \
              ASSERT(sizeof((PAR_PREF(param))) == sizeof(data)); \
              ATOMIC_BLOCK { (PAR_PREF(param)) = (data); } \
              } while(0);

// Get copy of dynamic parameter from parameter storage
//#define GET_PAR(param, data) do {
//              assert(sizeof((PAR_PREF(param))) == sizeof(data));
//              ATOMIC_BLOCK { (data) = (PAR_PREF(param)); }
//              } while(0);

// The macro to set default parameter value into NV memory
//ATOMIC_BLOCK { (PAR_PREF(param)) = (data); }
#define SET_PAR(param, data) do { \
                tLookupRegisters* pItem = NULL; \
                ATOMIC_BLOCK { *(&g_deviceDataStorage.param) = (data); } \
                pItem = this->getParDescrFromPtr(addr); \
                assert(pItem != NULL); \
                assert(sizeof(data) == pItem->size); \
                this->writeParameter(pItem, &data); \
              } while(0);

#define PARAM(parameter) &(holdingRegParams.parameter)

#define SET_DINAMYC_PAR(param, data) INIT_PAR(param, data)
#define GET_DINAMYC_PAR(param, data) GET_PAR(param, data)

#define SET_STATIC_PAR(param, data) SET_PAR(param, data)

#define MB_NVMGR_ENTER_CRITICAL(mux)    portENTER_CRITICAL(mux)
#define MB_NVMGR_EXIT_CRITICAL(mux)     portEXIT_CRITICAL(mux)

// NVS api provide lock functionality but data should be protected from multi task access
// This macro provides macro for atomic block to synchronize data access
#define ATOMIC_BLOCK for(int flag = enter_critical(); flag; flag = exit_critical())

#ifdef __cplusplus

class NvManager
{
public:
	    NvManager();
	    virtual ~NvManager();
	    esp_err_t writeParameter(tLookupRegisters *parInfo, void* paramData, uint8_t forceUpdate);
        esp_err_t readParameter(tLookupRegisters *parInfo, void* paramData);
        esp_err_t initDefault(void);
        esp_err_t readAllFromNv(void);
        tLookupRegisters* getParDescrFromPtr(void* parAddress);   
        
        template<typename T>
        esp_err_t writePar(T* addr, T data);
        esp_err_t initNv(void);
        esp_err_t getLastError(void);
        void setInitialDynamics(void);
protected:
        NvManager& oNvManager; // reference to this class from derived
        tLookupRegisters const* pLookupTable;
private:
        esp_err_t error;
        nvs_handle mbNvsHandle;
        uint8_t mbReadOnly;
        uint8_t mbNsIndex;
        esp_err_t nvsInitStatus;
};

extern NvManager* pNvManager;

#else
// The wrapper functions and "C" defines are defined here

#endif // __cplusplus

#endif // !defined(_CNVMANAGER)
