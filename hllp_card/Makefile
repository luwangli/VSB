GCC = g++
CFLAGS = -std=gnu++11 -Wall
SEEFLAGS = -march=native -msse2
SRC := $(wildcard *.c *.cpp)
OBJ :=$(patsubst %.c, %.o, $(SRC))
#SRC += ../SpreadSketch/hash.c ../SpreadSketch/bitmap.c ../SpreadSketch/spreadsketch.c
FILES = main.out

all:$(FILES)

main.out: $(OBJ)
	$(GCC) $^ -o $@
	#$(GCC) $(CFLAGS) $(SEEFLAGS) -o main.out main.cpp

clean:
	rm $(all) -f *~ *.o *.out *.txt *.csv core
