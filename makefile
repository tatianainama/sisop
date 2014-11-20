VPATH=/actors

all: server.o client.o local.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o timer.o actors/sidebar.o actors/stairs.o
	g++ -o server server.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread
	g++ -o client client.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread
	g++ -o local local.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

server: server.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o timer.o actors/sidebar.o actors/stairs.o
	g++ -o server server.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

client: client.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o timer.o actors/sidebar.o actors/stairs.o
	g++ -o client client.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

local: local.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o timer.o actors/sidebar.o actors/stairs.o
	g++ -o local local.o engine.o actors/floor.o actors/bonus.o iactor.o actors/monkey.o actors/mario.o actors/sidebar.o timer.o actors/stairs.o  -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread



server.o: server.cpp
	g++ -c server.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

client.o: client.cpp
	g++ -c client.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread
 
local.o: local.cpp
	g++ -c local.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread	


engine.o: engine.cpp engine.h constants.h
	g++ -c engine.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread


stairs.o: stairs.cpp stairs.h
	g++ -c stairs.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

floor.o: floor.cpp floor.h
	g++ -c floor.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread
bonus.o: bonus.cpp bonus.h
	g++ -c bonus.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

iactor.o: iactor.cpp iactor.h
	g++ -c iactor.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

mario.o: mario.cpp mario.h
	g++ -c mario.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

monkey.o: monkey.cpp monkey.h
	g++ -c monkey.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

timer.o: timer.cpp timer.h
	g++ -c timer.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread

sidebar.o: sidebar.cpp sidebar.h
	g++ -c sidebar.cpp -lSDL -lSDLmain -lSDL_image -lSDL_ttf -pthread


clean:
	rm -f *.o; 
	rm -f *.exe;
	rm -f *.cpp~;
	rm -f *.h~;
	rm -f actors/*.o

