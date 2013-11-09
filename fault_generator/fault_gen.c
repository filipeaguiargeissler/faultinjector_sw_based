/**
 * Initial Version 
 * faguiar@parks
 * UFRGS - microeletronics institute
 *
 *
 */

#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

#include "../qemu-1.6.0/fault_injection_module.h"

/* each memory position has 4 bytes (32 bits) */

static int verbose_flag;

static struct option long_options[] =
{
	/* These options set a flag. */
	{"verbose", no_argument,       &verbose_flag, 1},
	{"brief",   no_argument,       &verbose_flag, 0},
	{"app-total-time",  required_argument, 0, 't'},
	{"mem-init",  required_argument,       0, 'i'},
	{"mem-end",  required_argument, 0, 'e'},
	{"total-faults",  required_argument, 0, 'f'},
	{"output-file",    required_argument, 0, 'o'},
	{"range-init",    required_argument, 0, 'r'},
	{"range-end",    required_argument, 0, 'b'},
	{0, 0, 0, 0}
};

uint64_t random_in_range(uint64_t min, uint64_t max)
{
	uint64_t delta = max - min;

	return (rand() % delta) + min;
}

int main(int argc, char *argv[])
{
		int fd, c, i;
		char *file = NULL;
		uint64_t totalTime, memInit, memEnd, memRangeInit = 0, memRangeEnd = 0;
		uint32_t totalFaults;
		struct faultInjectionModuleStimule fims;

		while (1)
		{
			int option_index = 0;

			c = getopt_long (argc, argv, "t:i:e:f:o:r:b:",
							long_options, &option_index);

			/* Detect the end of the options. */
			if (c == -1)
					break;

			switch (c)
			{
			case 0:
					if (long_options[option_index].flag != 0)
							break;
					printf ("option %s", long_options[option_index].name);
					if (optarg)
							printf (" with arg %s", optarg);
					printf ("\n");
					break;

			case 't':
					//totalTime = 12000000000;
					totalTime = atol(optarg); // time ticks
					break;

			case 'i':
					memInit = atoi(optarg);
					break;

			case 'e':
					//memEnd = 33554432;
					memEnd = atol(optarg);
					break;

			case 'f':
					totalFaults = atol(optarg);
					break;

			case 'o':
					file = strdup(optarg);
					break;

			case 'r':
					memRangeInit = atoi(optarg);
					break;	

			case 'b':
					memRangeEnd = atoi(optarg);
					break;	

			case '?':
					/* getopt_long already printed an error message. */
					break;

			default:
					abort ();
			}
		}

		unlink(FAULT_STIMULI_FILE);

		fd = open(file, O_WRONLY | O_CREAT, 0666);
		if (fd == -1) {
				printf("Sorry! You can't crate a file :(\n");
				return -1;
		}

		write(fd, &totalTime, sizeof(totalTime));
		write(fd, &memInit, sizeof(memInit));
		write(fd, &memEnd, sizeof(memEnd));
		write(fd, &totalFaults, sizeof(totalFaults));

		printf("t=%ld i=%ld e=%ld f=%u o=%s\n", totalTime, memInit, memEnd, totalFaults, file);
		for (i = 0; i < totalFaults; i++) {
				memset(&fims, 0, sizeof(fims));
				fims.mode = rand() % FAULT_INJECTION_MODULE_MAX_TYPES;
				fims.mem_fault_type = rand() % FAULT_INJECTION_MODULE_MAX_MEM_FAULT_TYPES;
				fims.trigger = rand() % FAULT_INJECTION_MODULE_MAX_TRIGGER_TYPES;
				fims.duration = rand() % FAULT_INJECTION_MODULE_MAX_DURATION;
				if (memRangeEnd) {
						fims.addr = random_in_range(memRangeInit, memRangeEnd); 
				} else {
						fims.addr = random_in_range(memInit, memEnd);
				}
				fims.bit_pos = rand() % 8;
				fims.bit_val = rand() % 2;
				fims.start = rand() % totalTime;
				fims.end = totalTime;//random_in_range(fims.start, totalTime);
				write(fd, &fims, sizeof(fims));
				printf("debug mode=%d mem_fault=%d trigger=%d duration=%d time(%ld, %ld) softError(bit_pos, val)=(%x, %x) maddr=%lu\n", 
								fims.mode, fims.mem_fault_type,
								fims.trigger, fims.duration, fims.start, fims.end, fims.bit_pos, fims.bit_val,
								fims.addr);
		}

		fsync(fd);
		close(fd);

		return 0;
}
