PROGRAM=bounce
CC=g++
LD=g++
CFLAGS=-I. -c
LDFLAGS=-lncurses

all:  $(PROGRAM)

$(PROGRAM): OneBallMain.o Board.o
	$(LD) -o $@  OneBallMain.o Board.o $(LDFLAGS)

OneBallMain.o:  OneBallMain.cc Board.h
	$(CC) $(CFLAGS) $<

Board.o:  Board.cc Board.h
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o $(PROGRAM)
