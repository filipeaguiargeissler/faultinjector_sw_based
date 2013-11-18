#!/bin/bash
#
# Initial Version <filipeaguiar@gmail.com>
# Date: 11/17/2013
#

echo "Activating Simulation Debug"
tail -f /var/log/syslog &

echo "Generate Fault Vector"

cd fault_generator

# -t 	total ticks=12000000000 
# -i 	golden simulation mem_init=0 
# -e 	golden simulation mem_end=33554432 (128M)
# -f 	number of faults to be generated
# -o 	output file
# -r 	target mem fault mem_init=0x135488 
# -b 	target mem fault mem_end=0x1354A8
# -a 	number of registers
./fault-pattern -t 12000000000 -i 0 -e 33554432 -f 5 -o /home/filipe/mestrado/stimuli.txt -r 1266056 -b 1266856 -a 8
cd -

echo "Starting Simulation"
cd ../root
./bin/qemu-system-i386 -kernel ./i386-rtems4.11/pc386/lib/rtems-4.11/tests/hello.exe -nographic -m 128M -serial file:./log.txt
cd -
echo "Simulation Done"

echo "SIMULATION REPORTS"
echo ""
cat ../simul_reports.txt
echo ""

