#ifndef __FAULT_INJECTION_MODULE_H__
#define __FAULT_INJECTION_MODULE_H__

#include <unistd.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <syslog.h>

// enable fault injector module
#define FAULT_INJECTION_API  1

#define FAULT_STIMULI_FILE   "/home/filipe/mestrado/stimuli.txt"

#define FAULT_MEMRESULT_BIN   "/home/filipe/mestrado/memresult.bin"

#define FAULT_REPORTS_FILE   "/home/filipe/mestrado/simul_reports.txt"

// Simulation Mode
enum {
	FAULT_INJECTION_MODULE_DISABLED,
	FAULT_INJECTION_MODULE_GOLDEN_EXECUTION,
	FAULT_INJECTION_MODULE_WITH_FAULT,
};

enum {
	FAULT_INJECTION_MODULE_DEBUG_OFF,
	FAULT_INJECTION_MODULE_DEBUG_ON,
};

// Mode
enum {
	FAULT_INJECTION_MODULE_MEM_CELL_ARRAY,
	// FAULT_INJECTION_MODULE_DECODER,
	FAULT_INJECTION_MODULE_CPU_REGS,
	FAULT_INJECTION_MODULE_MAX_TYPES,
};

// Mem Fault Type 
enum {
	FAULT_INJECTION_MODULE_STUCK_AT_FAULT,	
	FAULT_INJECTION_MODULE_BITFLIP_FAULT,
	FAULT_INJECTION_MODULE_COUPLING_FAULT,
	FAULT_INJECTION_MODULE_MAX_MEM_FAULT_TYPES,
};

// CPU Fault Type
enum {
	FAULT_INJECTION_MODULE_CPU_REG_STUCK_AT_FAULT,
	FAULT_INJECTION_MODULE_CPU_REG_BITFLIP_FAULT,
//	FAULT_INJECTION_MODULE_CPU_REG_PC_FAULT,
	FAULT_INJECTION_MODULE_MAX_CPU_FAULT_TYPES,
};

// Decoder Fault type
enum {
	FAULT_INJECTION_MODULE_FAILURE_TO_ACCESS_CELL,
	FAULT_INJECTION_MODULE_WRONG_ACCESS_CELL,
	FAULT_INJECTION_MODULE_ACCESS_MANY_CELLS_FOR_ONE_ADDRESS,
	FAULT_INJECTION_MODULE_ACCESS_MANY_ADDRS_FOR_SAME_CELL,
};

// Trigger type
enum {
	FAULT_INJECTION_MODULE_TIME_BASED_TRIGGER,
	FAULT_INJECTION_MODULE_ACCESS_BASED_TRIGGER,
	FAULT_INJECTION_MODULE_MAX_TRIGGER_TYPES,
};

// Duration
enum {
	FAULT_INJECTION_MODULE_TRANSIENT,
	FAULT_INJECTION_MODULE_PERMANENT,
	FAULT_INJECTION_MODULE_INTERMITTENT,
	FAULT_INJECTION_MODULE_MAX_DURATION,
};

struct faultInjectionModuleStimule {
	int mode;
	int mem_fault_type;
	int decoder_fault_type;
	int cpu_fault_type;
	int trigger;
	int duration;

	uint64_t addr;
	int reg_idx;
	int bit_pos;
	int bit_val;
	int64_t start;
	int64_t end;

	// Used by the QEMU software
#define INVALID_VAL  (0x00000)
#define VALID_VAL    (0x00001)
	uint8_t flags;
	uint8_t val[4];
};

struct faultInjectionStatistics {
	uint8_t *pMemDump;
	unsigned long dataflow_err;
	unsigned long datapath_err;
};

struct faultInjectionModule {
	// Fault injection mode
	int mode;
	// Configure debug mode
	int debug;

	// When this time is reach the system is restarted
	// end a new simulation is executed
	int64_t simultotalTime; 

	// The first simulation is to do a golden execution
	uint64_t goldenMemInit;
	uint64_t goldenMemEnd;
	uint32_t goldenMemLen;

	// Allocated memory with system expected results
	uint8_t *pResults;	
	int resultsLen;
	uint8_t resultsIdxGoldenMem;
	
	// Allocated memory with golden execution result
	// i386 arch
	uint8_t *goldenMemDump;
	
	// Depends on the number of stimuli in the input file
	int stimuliTotal;
	int idx;
	struct faultInjectionModuleStimule *list;

	struct faultInjectionStatistics stats;
};


int fault_injection_module_check_and_trigger(void);

#endif

