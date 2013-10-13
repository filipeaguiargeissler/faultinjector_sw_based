/**
 * Autor: faguiar@parks
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../qemu-1.6.0/fault_injection_module.h"


int main(int argc, char *argv[])
{
	int fd;
	struct faultInjectionModuleStimule fims;
	uint64_t totalTime;
	uint64_t memInit, memEnd;

	unlink(FAULT_STIMULI_FILE);

	fd = open(FAULT_STIMULI_FILE, O_WRONLY | O_CREAT, 0666);
	if (fd == -1) {
		printf("Sorry! You can't crate a file :(\n");
		return -1;
	}

	totalTime = 10002000000;
	write(fd, &totalTime, sizeof(totalTime));
	
	// 128M

	memInit = 0x0;
	write(fd, &memInit, sizeof(memInit));

	memEnd = 33554432;
	write(fd, &memEnd, sizeof(memEnd));

	memset(&fims, 0, sizeof(fims));
	fims.mode = FAULT_INJECTION_MODULE_MEM_CELL_ARRAY;
	fims.mem_fault_type = FAULT_INJECTION_MODULE_BITFLIP_FAULT;
	fims.trigger = FAULT_INJECTION_MODULE_TIME_BASED_TRIGGER;
	fims.fault_type = FAULT_INJECTION_MODULE_TRANSIENT;
	fims.addr = 0x10000;
	fims.bit_pos = 0;
	fims.bit_val = 1;
	fims.start = 500000000000;
	fims.end = 500001000000;
	write(fd, &fims, sizeof(fims));

	fsync(fd);
	close(fd);

	return 0;
}
