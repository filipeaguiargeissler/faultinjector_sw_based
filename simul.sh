#!/bin/bash

echo "Generate Software Vector"

cd fault_generator
./fault-pattern -t 12000000000 -i 0 -e 33554432 -f 5 -o /home/filipe/mestrado/stimuli.txt -r 136 -b 220
cd -

echo "Activating Simulation Debug"
tail -f /var/log/syslog &

echo "Starting Simulation"
cd ../root
./bin/qemu-system-i386 -kernel ./i386-rtems4.11/pc386/lib/rtems-4.11/tests/hello.exe -nographic -m 128M -serial file:./log.txt
cd -
echo "Simulation Done"

echo "SIMULATION REPORTS"
echo ""
cat ../simul_reports.txt
echo ""

