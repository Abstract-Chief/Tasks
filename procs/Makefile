CC=g++ #varible
CCFLAGS= -g -Wall
LIBS=-lm -lncurses

PROG=parser.cpp\
	  process.cpp

create_lib:
	$(CC) $(CCFLAGS) -D SYSTEM_TYPE=64 $(PROG) $(GENERAL) -c $(LIBS)
	ar cr proc.lib *.o
	rm *.o
	ranlib proc.lib
