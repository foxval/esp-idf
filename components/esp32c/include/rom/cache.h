// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _ROM_CACHE_H_
#define _ROM_CACHE_H_


#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup cache_apis, cache operation related apis
  * @brief cache apis
  */

/** @addtogroup cache_apis
  * @{
  */

#define ESP_CACHE_TEMP_ADDR DROM0_ADDRESS_LOW
#define CACHE_MAX_OPERATION_SIZE 0x40000

typedef enum {
    CACHE_MEMORY_INVALID = 0,
    CACHE_MEMORY_ICACHE_LOW = BIT(0),
    CACHE_MEMORY_ICACHE_HIGH = BIT(1),
    CACHE_MEMORY_DCACHE_LOW = BIT(2),
    CACHE_MEMORY_DCACHE_HIGH = BIT(3),
} cache_layout_t;

typedef enum {
    CACHE_SIZE_8KB = 0,
    CACHE_SIZE_16KB = 1,
} cache_size_t;

typedef enum {
    CACHE_4WAYS_ASSOC = 0,
    CACHE_8WAYS_ASSOC = 1,
} cache_ways_t;

typedef enum {
    CACHE_LINE_SIZE_16B = 0,
    CACHE_LINE_SIZE_32B = 1,
    CACHE_LINE_SIZE_64B = 2,
} cache_line_size_t;

#define MMU_SET_ADDR_ALIGNED_ERROR	1
#define MMU_SET_PASE_SIZE_ERROR		3
#define MMU_SET_VADDR_OUT_RANGE		5

/**
  * @brief Initialise cache mmu, mark all entries as invalid.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @return None
  */
void mmu_init(int cpu_no);

/**
  * @brief Set ICache mmu mapping.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @param  unsigned int ext_ram : DPORT_MMU_ACCESS_FLASH for flash, DPORT_MMU_ACCESS_SPIRAM for spiram, DPORT_MMU_INVALID for invalid.
  *
  * @param  unsigned int vaddr : virtual address in CPU address space.
  *                              Can be Iram0,Iram1,Irom0,Drom0 and AHB buses address.
  *                              Should be aligned by psize.
  *
  * @param  unsigned int paddr : physical address in external memory.
  *                              Should be aligned by psize.
  *
  * @param  int psize : page size of ICache, in kilobytes. Should be 64 here.
  *
  * @param  int num : pages to be set.
  *
  * @return unsigned int: error status
  *                   0 : mmu set success
  *                   1 : vaddr or paddr is not aligned
  *                   3 : psize error
  *                   5 : vaddr is out of range
  */
int Cache_Ibus_MMU_Set(int cpu_no, unsigned int ext_ram, unsigned int vaddr, unsigned int paddr,  int psize, int num);

/**
  * @brief Set DCache mmu mapping.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @param  unsigned int ext_ram : DPORT_MMU_ACCESS_FLASH for flash, DPORT_MMU_ACCESS_SPIRAM for spiram, DPORT_MMU_INVALID for invalid.
  *
  * @param  unsigned int vaddr : virtual address in CPU address space.
  *                              Can be DRam0, DRam1, DRom0, DPort and AHB buses address.
  *                              Should be aligned by psize.
  *
  * @param  unsigned int paddr : physical address in external memory.
  *                              Should be aligned by psize.
  *
  * @param  int psize : page size of flash, in kilobytes. Should be 64 here.
  *
  * @param  int num : pages to be set.
  *
  * @return unsigned int: error status
  *                   0 : mmu set success
  *                   1 : vaddr or paddr is not aligned
  *                   3 : psize error
  *                   5 : vaddr is out of range
  */
int Cache_Dbus_MMU_Set(int cpu_no, unsigned int ext_ram, unsigned int vaddr, unsigned int paddr, int psize, int num);

/**
  * @brief allocate memory to used by ICache and DCache.
  *        Please do not call this function in your SDK application.
  *
  * @param cache_layout_t sram0_layout : the usage of first 8KB internal memory block, can be CACHE_MEMORY_INVALID, CACHE_MEMORY_ICACHE_LOW, CACHE_MEMORY_ICACHE_HIGH, CACHE_MEMORY_DCACHE_LOW and CACHE_MEMORY_DCACHE_HIGH
  *
  * @param cache_layout_t sram1_layout : the usage of second 8KB internal memory block 
  *
  * @param cache_layout_t sram2_layout : the usage of third 8KB internal memory block 
  *
  * @param cache_layout_t sram3_layout : the usage of forth 8KB internal memory block 
  *
  * return none
  */
void Cache_Allocate_SRAM(cache_layout_t sram0_layout, cache_layout_t sram1_layout, cache_layout_t sram2_layout, cache_layout_t sram3_layout);

/**
  * @brief set ICache modes: cache size, associate ways and cache line size.
  *        Please do not call this function in your SDK application.
  *
  * @param cache_size_t cache_size : the cache size, can be CACHE_SIZE_8KB and CACHE_SIZE_16KB
  *
  * @param cache_ways_t ways : the associate ways of cache, cane be CACHE_4WAYS_ASSOC and CACHE_8WAYS_ASSOC 
  *
  * @param cache_line_size_t cache_line_size : the cache line size, can be CACHE_LINE_SIZE_16B, CACHE_LINE_SIZE_32B and CACHE_LINE_SIZE_64B 
  *
  * @param cache_layout_t sram3_layout : the usage of forth 8KB internal memory block 
  *
  * return none
  */
void Cache_Set_ICache_Mode(cache_size_t cache_size, cache_ways_t ways, cache_line_size_t cache_line_size);

/**
  * @brief set DCache modes: cache size, associate ways and cache line size.
  *        Please do not call this function in your SDK application.
  *
  * @param cache_size_t cache_size : the cache size, can be CACHE_SIZE_8KB and CACHE_SIZE_16KB
  *
  * @param cache_ways_t ways : the associate ways of cache, cane be CACHE_4WAYS_ASSOC and CACHE_8WAYS_ASSOC 
  *
  * @param cache_line_size_t cache_line_size : the cache line size, can be CACHE_LINE_SIZE_16B, CACHE_LINE_SIZE_32B and CACHE_LINE_SIZE_64B 
  *
  * @param cache_layout_t sram3_layout : the usage of forth 8KB internal memory block 
  *
  * return none
  */
void Cache_Set_DCache_Mode(cache_size_t cache_size, cache_ways_t ways, cache_line_size_t cache_line_size);

/**
  * @brief check if the address is accessed through ICache.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @param  uint32_t addr : the address to check.
  *
  * @return 1 if the address is accessed through ICache, 0 if not.
  */
int Cache_Address_Through_ICache(int cpu_no, uint32_t addr);

/**
  * @brief check if the address is accessed through DCache.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @param  uint32_t addr : the address to check.
  *
  * @return 1 if the address is accessed through DCache, 0 if not.
  */
int Cache_Address_Through_DCache(int cpu_no, uint32_t addr);

/**
  * @brief Invalidate the cache items for ICache.
  *        Operation will be done CACHE_LINE_SIZE aligned.
  *        If the addr is not in our addr room, we will Flush all Cache.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @param  uint32_t addr: start address to invalidate
  *
  * @param  uint32_t size: size to invalidate, should <= 4MB
  *
  * @return None
  */
void Cache_Invalidate_ICache_Items(int cpu_no, uint32_t addr, uint32_t size);

/**
  * @brief Invalidate the cache items for DCache.
  *        Operation will be done CACHE_LINE_SIZE aligned.
  *        If the addr is not in our addr room, we will Flush all Cache.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @param  uint32_t addr: start address to invalidate
  *
  * @param  uint32_t size: size to invalidate, should <= 4MB
  *
  * @return None
  */
void Cache_Invalidate_DCache_Items(int cpu_no, uint32_t addr, uint32_t size);

/**
  * @brief Clean the dirty bit of cache Items of DCache.
  *        Operation will be done CACHE_LINE_SIZE aligned.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @param  uint32_t addr: start address to Clean
  *
  * @param  uint32_t size: size to Clean, should <= 4MB
  *
  * @return None
  */
void Cache_Clean_Items(int cpu_no, uint32_t addr, uint32_t size);

/**
  * @brief Write back the cache items of DCache.
  *        Operation will be done CACHE_LINE_SIZE aligned.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @param  uint32_t addr: start address to write back
  *
  * @param  uint32_t size: size to write back, should <= 4MB
  *
  * @return None
  */
void Cache_WriteBack_Items(int cpu_no, uint32_t addr, uint32_t size);

/**
  * @brief Invalidate the Cache items in the region from ICache or DCache.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @param  uint32_t addr : invalidated region start address.
  *
  * @param  uint32_t size : invalidated region size.
  *
  * @return None
  */
void Cache_Invalidate_Addr(int cpu_no, uint32_t addr, uint32_t size);

/**
  * @brief Clean the dirty bit of Cache items in the region from DCache.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @param  uint32_t addr : cleaned region start address.
  *
  * @param  uint32_t size : cleaned region size.
  *
  * @return None
  */
void Cache_Clean_Addr(int cpu_no, uint32_t addr, uint32_t size);

/**
  * @brief Writeback the Cache items(also clean the dirty bit) in the region from DCache.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @param  uint32_t addr : writeback region start address.
  *
  * @param  uint32_t size : writeback region size.
  *
  * @return None
  */
void Cache_WriteBack_Addr(int cpu_no, uint32_t addr, uint32_t size);


/**
  * @brief Invalidate all cache items in ICache.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @return None
  */
void Cache_Invalidate_ICache_All(int cpu_no);

/**
  * @brief Invalidate all cache items in DCache.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @return None
  */
void Cache_Invalidate_DCache_All(int cpu_no);

/**
  * @brief Clean the dirty bit of all cache items in DCache.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @return None
  */
void Cache_Clean_All(int cpu_no);

/**
  * @brief WriteBack all cache items in DCache.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : CPU number, insignificant in Chip7.2.2.
  *
  * @return None
  */
void Cache_WriteBack_All(int cpu_no);

/**
  * @brief Mask all buses through ICache and DCache.
  *        Please do not call this function in your SDK application.
  *
  * @param  None
  *
  * @return None
  */
void Cache_Mask_All(void);

/**
  * @brief UnMask DRom0 bus through ICache or DCache.
  *        Please do not call this function in your SDK application.
  *
  * @param  None
  *
  * @return None
  */
void Cache_UnMask_Drom0(void);

/**
  * @brief Copy DRom0 ICache MMU to DCache MMU.
  *        Please do not call this function in your SDK application.
  *
  * @param  None
  *
  * @return None
  */
void Cache_Drom0_MMU_Copy(void);

/**
  * @brief Disable Cache access for the cpu.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : 0 for PRO cpu, 1 for APP cpu.
  *
  * @return None
  */
void Cache_Read_Disable(int cpu_no);

/**
  * @brief Enable Cache access for the cpu.
  *        Please do not call this function in your SDK application.
  *
  * @param  int cpu_no : 0 for PRO cpu, 1 for APP cpu.
  *
  * @return None
  */
void Cache_Read_Enable(int cpu_no);

void Cache_Drom0_Source_ICache();

void Cache_Drom0_Source_DCache();

int Cache_Drom0_Using_ICache();

int Cache_Drom0_Using_DCache();

int Get_ICache_Block_Size();

int Get_DCache_Block_Size();

void Cache_Set_Default_Mode(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* _ROM_CACHE_H_ */
