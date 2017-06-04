# Makefile for bench/getmem/freemem/get_mem_stats/print_heap program
# CSE 374 HW 6, Yunsi Mou, Feb 21 2017

# default target
bench: bench.o getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils.o
	gcc -Wall -g -std=c11 -o bench bench.o getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils.o

# individual source files
getmem.o: getmem.c mem_impl.h 
	gcc -Wall -g -std=c11 -c getmem.c

freemem.o: freemem.c mem_impl.h
	gcc -Wall -g -std=c11 -c freemem.c

get_mem_stats.o: get_mem_stats.c  mem_impl.h
	gcc -Wall -g -std=c11 -c get_mem_stats.c

print_heap.o: print_heap.c mem_impl.h
	gcc -Wall -g -std=c11 -c print_heap.c

mem_utils.o: mem_utils.c mem_impl.h
	gcc -Wall -g -std=c11 -c mem_utils.c

bench.o: bench.c mem.h
	gcc -Wall -g -std=c11 -c bench.c

# Run the bench test program with default parameters
test:
	./bench

test10:
	./bench 10

test500:
	./bench 500

test42:
	./bench 42

testlarge:
	./bench 10000000

# Remove any .o files, executable, emacs backup files (*~) and any other files generated as part of making the program
clean:
	rm -f *.o bench *~

