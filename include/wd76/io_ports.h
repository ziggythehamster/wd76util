#ifndef _IO_PORTS_H
#define _IO_PORTS_H

#define IO_48MHZ_OSC_DISABLE              0xF072
#define IO_48MHZ_OSC_ENABLE               0xF472
#define IO_ACTIVITY_MONITOR_CONTROL       0xB072
#define IO_ACTIVITY_MONITOR_MASK          0xD872
#define IO_BANK01_START_ADDRESS           0x4872
#define IO_BANK23_START_ADDRESS           0x5072
#define IO_BUS_TIMING                     0x1872
#define IO_CACHE_FLUSH                    0xF872
#define IO_CHIP_SELECT_1                  0x2072
#define IO_CHIP_SELECT_2                  0x2872
#define IO_CHIP_SELECT_ADDRESS            0x3072
#define IO_CPU_CLOCK_CONTROL              0x1072
#define IO_DELAY_LINE                     0xA072
#define IO_DIAGNOSTIC                     0x9872
#define IO_DMA_CONTROL_SHADOW             0xB872
#define IO_EMS_CONTROL                    0x6872
#define IO_EMS_LOWER_BOUNDARY             0x6872
#define IO_EMS_PAGE_REGISTER              0xE872
#define IO_EMS_PAGE_REGISTER_POINTER      0xE072
#define IO_HIGHMEM_WRITE_PROTECT_BOUNDARY 0xC072
#define IO_INTERRUPT_CONTROLLER_SHADOW    0xD472
#define IO_LOCK_STATUS                    0xFC72
#define IO_LOCK_UNLOCK                    0xF073
#define IO_MEMORY_CONTROL                 0x3872
#define IO_NMI_STATUS                     0x9082
#define IO_NONPAGE_DRAM_TIMING            0x4072
#define IO_PMC_INPUTS                     0x8872
#define IO_PMC_INTERRUPT_ENABLES          0xC872
#define IO_PMC_OUTPUT_CONTROL_H           0x7872
#define IO_PMC_OUTPUT_CONTROL_L           0x7072
#define IO_PMC_TIMERS                     0x8072
#define IO_PORT_70H_SHADOW                0xE472
#define IO_POWER_DOWN_CONTROL             0x1872
#define IO_RAM_SHADOW                     0x6072
#define IO_RAM_WRITE_PROTECT              0x6072
#define IO_REFRESH_CONTROL                0x2072
#define IO_SERIAL_PARALLEL_SHADOW         0xD072
#define IO_SPLIT_START_ADDRESS            0x5872
#define IO_TEST_ENABLE                    0xA872
#define IO_TEST_STATUS                    0xDC72

#endif
