/**
 * Autor: faguiar@parks
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unstd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../qemu-1.6.0/fault_injection_module.h"


int main(int argc, char *argv[])
{
	int fd;
	struct faultInjectionModuleStimule fims;

	fd = open(FAULT_STIMULI_FILE, O_WRONLY | O_CREAT);
	if (fd == -1) {
		printf("Sorry! You can't crate a file :(\n");
		return -1
	}

	memset(&fims);
	fims.mode = FAULT_INJECTION_MODULE_MEM_CELL_ARRAY;
	fims.mem_fault_type = FAULT_INJECTION_MODULE_BITFLIP_FAULT;
	fims.trigger = FAULT_INJECTION_MODULE_TIME_BASED_TRIGGER;
	fims.fault_type = FAULT_INJECTION_MODULE_TRANSIENT;
	fims.addr = 0x10000;
	fims.bit_post = 0;
	fims.bit_val = 1;
	fims.bit_val = 10000000000;
	fims.bit_val = 10001000000;
	write(fd, &fims, sizeof(fims));

	fsync(fd);
	close(fd);

	return 0;
}
