all:
	g++ game.cpp game.h -o VraXaPsaIII -lglut -lGLU -lGL

clean:
	rm VraXaPsaIII
