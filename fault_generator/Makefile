##################################
#
# initial version: faguiar@
#
##################################

CC=gcc
CFLAGS=-I.
DEPS = 
OBJ = fault_gen.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

fault-pattern: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o fault-pattern
