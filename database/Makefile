CC=g++ #varible
CCFLAGS= -g -Wall
LIBS=-lm -lncurses


PROG=src/database.cpp\
	  src/dhandler.cpp

create_lib:
	$(CC) $(CCFLAGS) $(PROG) $(GENERAL) -c $(LIBS)
	ar cr dhandler.lib *.o
	rm *.o
	ranlib dhandler.lib
