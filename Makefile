

all: demo inoup

demo: LightHeroDemo demo.o demo.h lighthero.h
	gcc demo.o -o demo

demo.o: demo.c demo.h lighthero.h
	gcc -c demo.c -o demo.o

LightHeroDemo: LightHeroDemo.java
	javac LightHeroDemo.java

inoup: inobuild
	cd nano; ino upload -m nano328

nano/src:
	cd nano; ino init
	cd nano/src; rm -rf *

inobuild: nano nano/src nano/src/ino.c
	cd nano; ino build -m nano328

nano/src/ino.c: ino.c
	cp ino.c nano/src/ino.c

nano:
	mkdir nano
	cd nano; rm -rf *

clean:
	rm -f *.class
	rm -f LightHeroDemo
	rm -f *.o
	rm -rf nano



