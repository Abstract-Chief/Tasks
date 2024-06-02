CC=g++ #varible
CCFLAGS= -g -Wall

LIBS=-lm -lncursesw

PROG=Label/label.cpp \
	  Geometry/geometry.cpp \
	  QtObject/object.cpp\
	  QtObject/ActionQtObject.cpp \
	  Button/button.cpp\
	  Conteiner/list.cpp\
	  ProgressBar/ProgressBar.cpp\
	  Conteiner/box.cpp\
	  tasks/TaskObject.cpp\
	  Notice/notice.cpp

create_lib:
	$(CC) $(CCFLAGS) -lncursesw $(PROG) $(GENERAL) -c $(LIBS)
	@ar cr ../lib/object.lib *.o
	@rm *.o
	@ranlib ../lib/object.lib

clean:
	rm *.o
