CC=g++ #varible
CCFLAGS= -g -Wall
LIBS=-lm -lncursesw


PROG=screen/screen.cpp  app.cpp

library: 
	@cd objects ; make create_lib ; cd ..
	@echo "успешно скомпилирована библиотека объектов"

engine: 
	@$(CC) $(CCFLAGS) $(PROG) -c $(LIBS)
	ar cr lib/engine.lib *.o
	rm *.o
	ranlib lib/engine.lib

create_lib: engine library
	@echo "create library ui(engine and objects)"

compilate: create_lib
	@$(CC) main.cpp lib/object.lib lib/engine.lib ../../procs/proc.lib $(CCFLAGS) -o build $(LIBS)
	@echo "успешная компиляция"

prog: compilate
	@echo "Run"
	@echo ""
	./build

clean:
	rm *.o
