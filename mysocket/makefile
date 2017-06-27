.PHONY: src
src:
	g++ Filerw.cpp Speed.cpp Socket.cpp Client.cpp MainClient.cpp -o ../Client/client
	g++ Filerw.cpp Speed.cpp Socket.cpp Server.cpp MainServer.cpp -o ../Server/server

.PHONY: clean
clean:
	-rm edit $(objects)
