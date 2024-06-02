CC=g++ #varible
CCFLAGS= -g -Wall
LIBS=-lsqlite3 -lncurses -lncursesw

GENERAL=general/general.lib\
		  database/dhandler.lib\
		  procs/proc.lib

USER=user/packet/my_packet.cpp\
	  user/session/my_session.cpp

SERVERC=server/server.cpp server/module/ServerBase.cpp server/handler_command/command.cpp

KLIENTC=klient/klient.cpp klient/module/BaseKlient.cpp server/module/ServerBase.cpp \
		  klient/config/net_conf.cpp klient/config/input_conf.cpp klient/config/ui.cpp\
		  klient/UI/lib/engine.lib klient/UI/lib/object.lib klient/command/ksk_command.cpp

general_comp:
	@cd general ; make create_lib ; cd -
	@echo "успешно скомпилирована библиотека general"

proc_comp:
	@cd procs ; make create_lib ; cd -
	@echo "успешно скомпилирована библиотека procs"

database_comp:
	@cd database ; make create_lib ; cd -
	@echo "успешно скомпилирована библиотека database"

klient_comp: general_comp database_comp proc_comp
	@cd klient/UI ; make create_lib ; cd -
	$(CC) $(CCFLAGS) $(KLIENTC) $(USER) $(GENERAL) -o build/klient $(LIBS)
	@echo "клиент успешно скомпилирован"

server_comp: general_comp database_comp proc_comp
	@$(CC) $(CCFLAGS) $(SERVERC) $(USER) $(GENERAL) -o build/server $(LIBS)
	@echo "сервер успешно скомпилирован"

server: server_comp
	@echo "запуск сервера"
	@echo ""
	@build/server

klient_l: klient_comp
	@echo "запуск клиента"
	@echo ""
	@build/klient 127.0.0.1

k_grisha: klient_l
	build/klient < build/grisha_log

k_artem: klient_l
	build/klient < build/artem_log

clean:
	rm *.o
