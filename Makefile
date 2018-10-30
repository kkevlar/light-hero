

all: demo

demo: LightHeroDemo demo.o demo.h lighthero.h
	gcc demo.o -o demo

demo.o: demo.c demo.h lighthero.h
	gcc -c demo.c -o demo.o

LightHeroDemo: LightHeroDemo.java
	javac LightHeroDemo.java


