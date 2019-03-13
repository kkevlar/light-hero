
INOMAKE_NORMAL_DEPS=ino/Makefile \
ino/ino.cpp\
ino/ino.h\
ino/justin.cpp\
ino/justin.h\
ino/lighthero.cpp\
ino/lighthero.h\
ino/platform.h

INOMAKE_SPECIAL_DEPS=ino \
ino/Arduino-Makefile \

all: ino inomake

ino:
	mkdir -p ino

ino/Makefile: INO-Makefile | ino
	cp INO-Makefile ino/Makefile

ino/Arduino-Makefile: | ino
	cd ino && git clone git@github.com:sudar/Arduino-Makefile.git

ino/lighthero.cpp: lighthero/lighthero.ino | ino
	cp lighthero/lighthero.ino ino/lighthero.cpp

ino/lighthero.h: lighthero/lighthero.h | ino
	cp lighthero/lighthero.h ino/lighthero.h

ino/justin.h: lighthero/justin.h | ino
	cp lighthero/justin.h ino/justin.h

ino/justin.cpp: lighthero/justin.ino | ino
	cp lighthero/justin.ino ino/justin.cpp

ino/ino.h: lighthero/ino.h | ino
	cp lighthero/ino.h ino/ino.h

ino/ino.cpp: lighthero/ino.ino | ino
	cp lighthero/ino.ino ino/ino.cpp

ino/platform.h: lighthero/platform.h | ino
	cp lighthero/platform.h ino/platform.h

inomake: $(INOMAKE_NORMAL_DEPS) | $(INOMAKE_SPECIAL_DEPS)
	cd ino && make

upload: inomake
	cd ino && make upload

purge: clean
	rm -rf ino

clean:
	cp -rf ino/Arduino-Makefile .
	rm -rf ino
	mkdir -p ino
	mv Arduino-Makefile ino

