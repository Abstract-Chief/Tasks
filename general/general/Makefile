CC=g++ #varible
CCFLAGS= -g -Wall
LIBS=-lm -lncurses


PROG=session/session.cpp\
	  packet/packet.cpp\
	  handler/handler.cpp perl/perl.cpp\
	  inet_base/InternetBase.cpp

create_lib:
	$(CC) $(CCFLAGS) $(PROG) $(GENERAL) -c $(LIBS)
	ar cr general.lib *.o
	rm *.o
	ranlib general.lib
