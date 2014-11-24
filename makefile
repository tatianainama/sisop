VPATH=/actors

all: server.o client.o local.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o timer.o actors/sidebar.o actors/stairs.o
	g++ -o server server.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread -lrt
	g++ -o client client.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread
	g++ -o local local.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

server: server.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o timer.o actors/sidebar.o actors/stairs.o
	g++ -o server server.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

client: client.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o timer.o actors/sidebar.o actors/stairs.o
	g++ -o client client.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

local: local.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o timer.o actors/sidebar.o actors/stairs.o
	g++ -o local local.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread


servert: server_t.c
	gcc -o servert  server_t.c -lpthread -lSDL -lSDL_image -lSDL_ttf -lm -lrt


server.o: server.cpp
	g++ -c server.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -lpthread -lrt

client.o: client.cpp
	g++ -c client.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -lpthread
 
local.o: local.cpp
	g++ -c local.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -lpthread


engine.o: engine.cpp engine.h constants.h
	g++ -c engine.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -lpthread


stairs.o: stairs.cpp stairs.h
	g++ -c stairs.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -lpthread

floor.o: floor.cpp floor.h
	g++ -c floor.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -lpthread
bonus.o: bonus.cpp bonus.h
	g++ -c bonus.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -lpthread

iactor.o: iactor.cpp iactor.h
	g++ -c iactor.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -lpthread

mario.o: mario.cpp mario.h
	g++ -c mario.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

monkey.o: monkey.cpp monkey.h
	g++ -c monkey.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -lpthread

timer.o: timer.cpp timer.h
	g++ -c timer.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -lpthread

sidebar.o: sidebar.cpp sidebar.h
	g++ -c sidebar.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -lpthread


clean:
	rm -f *.o; 
	rm -f *.exe;
	rm -f *.cpp~;
	rm -f *.h~;
	rm -f actors/*.o

