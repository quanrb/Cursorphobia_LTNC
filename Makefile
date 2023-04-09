compile:
	g++ -Iinclude -Iinclude/sdl -Llib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

run:
	g++ -Iinclude -Iinclude/sdl -Llib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	./main.exe

run-only:
	./main.exe