CC=gcc
CFLAGS=-Wall -I.
DEPS = ciaAllocation.h
OBJ = allocation.o setMags.o ciaAllocationUnitTests.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o test $(OBJ)

.PHONY: clean

clean:
	rm -f *.o *~ core