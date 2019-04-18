

all: bin/p1 bin/p2 bin/p3 bin/p4 bin/p5 bin/raw2vlf

carpets:
	mkdir bin img lib obj

bin/test: src/test.c lib/libgraph.a
	gcc src/test.c -o bin/test -g -Wall -Iinclude -Llib -lgraph -lm


bin/p1: src/practica1.c lib/libgraph.a
	gcc src/practica1.c -o bin/p1 -g -Wall -Iinclude -Llib -lgraph -lm

bin/p2: src/practica2.c lib/libgraph.a
	gcc src/practica2.c -o bin/p2 -g -Wall -Iinclude -Llib -lgraph -lm

bin/p3: src/practica3.c lib/libgraph.a
	gcc src/practica3.c -o bin/p3 -g -Wall -Iinclude -Llib -lgraph -lm

bin/p4: src/practica4.c lib/libgraph.a
	gcc src/practica4.c -o bin/p4 -g -Wall -Iinclude -Llib -lgraph -lm

bin/p5: src/practica5.c lib/libgraph.a
	gcc src/practica5.c -o bin/p5 -g -Wall -Iinclude -Llib -lgraph -lm

bin/raw2vlf: src/raw2vlf.c lib/libformat.a lib/libgraph.a
	gcc src/raw2vlf.c -o bin/raw2vlf -g -Wall -Iinclude -Llib -lgraph -lformat

lib/libgraph.a: obj/libgraph.o
	ar -rv lib/libgraph.a obj/libgraph.o
	ranlib lib/libgraph.a

obj/libgraph.o: src/myGraphics.c include/myGraphics.h
	gcc -c src/myGraphics.c -Iinclude -g -Wall -o obj/libgraph.o

lib/libformat.a: obj/libformat.o
	ar -rv lib/libformat.a obj/libformat.o
	ranlib lib/libformat.a

obj/libformat.o: src/formats3d.c include/formats3d.h
	gcc -c src/formats3d.c -Iinclude -g -Wall -o obj/libformat.o



clean:
	rm bin/* lib/*.a obj/*.o img/*.gif
