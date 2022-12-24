all:
	g++ -I SDL2_files/include -L SDL2_files/lib main.cpp -lmingw32 -lSDL2main -lSDL2