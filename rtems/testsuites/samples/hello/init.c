/*
 *  COPYRIGHT (c) 1989-2012.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <bsp.h> /* for device driver prototypes */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* forward declarations to avoid warnings */
rtems_task Init(rtems_task_argument argument);

rtems_task Init(
  rtems_task_argument ignored
)
{
  int i;
  unsigned int *vet;

  vet = malloc(sizeof(int)*200);
	
  printf( "\n\n*** HELLO WORLD TEST ***\n" );
  printf( "Hello World\n" );
  printf( "*** END OF HELLO WORLD TEST ***\n" );

  for (i = 0; i < 200; i++)
					vet[i] = 0xabababab;

  while (1)
	sleep(1);

  exit( 0 );
}


/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_TASKS            1
#define CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
