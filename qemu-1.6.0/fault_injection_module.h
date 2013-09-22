#ifndef __FAULT_INJECTION_MODULE_H__
#define __FAULT_INJECTION_MODULE_H__

#define FAULT_STIMULI_FILE   "/home/filipe/mestrado/stimuli.txt"

#define FAULT_INJECTION_MAX  (10000)

// Simulation Mode
enum {
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
	FAULT_INJECTION_MODULE_DECODER
}

// Mem Fault Type 
enum {
	FAULT_INJECTION_MODULE_STUCK_AT_FAULT,	
	FAULT_INJECTION_MODULE_BITFLIP_FAULT,
	FAULT_INJECTION_MODULE_COUPLING_FAULT,
};

// Decoder Fault type
enum {
	FAULT_INJECTION_MODULE_FAILURE_TO_ACCESS_CELL,
	FAULT_INJECTION_MODULE_WRONG_ACCESS_CELL,
	FAULT_INJECTION_MODULE_ACCESS_MANY_CELLS_FOR_ONE_ADDRESS,
	FAULT_INJECTION_MODULE_ACCESS_MANY_ADDRS_FOR_SAME_CELL,
};

// Trigger
enum {
	FAULT_INJECTION_MODULE_TIME_BASED_TRIGGER,
	FAULT_INJECTION_MODULE_ACCESS_BASED_TRIGGER
}

// Fault type
enum {
	FAULT_INJECTION_MODULE_TRANSIENT,
	FAULT_INJECTION_MODULE_PERMANENT,
	FAULT_INJECTION_MODULE_INTERMITTENT,
}

struct faultInjectionModuleStimule {
	int mode;
	int mem_fault_type;
	int decoder_fault_type;
	int trigger;
	int fault_type;

	uint64_t addr;
	int bit_pos;
	int bit_val;
	int64_t start;
	int64_t end;
};

struct faultInjectionStatistics {
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
	
	// Allocated memory with golden execution result
	// i386 arch
	unsigned int *goldenMemDump;
	
	// Depends on the number of stimuli in the input file
	int stimuliTotal;
	int idx;
	struct faultInjectionModuleStimule list[FAULT_INJECTION_MAX];

	struct faultInjectionStatistics stats;
};

#endif
