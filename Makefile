OUTPUT_BIN=Console-Tank.exe
CCTAGS_STD=c99
CCTAGS_DEBUG=1
# SYSROOT="~/../../cygwin64/usr/i686-pc-cygwin/sys-root/"
SYSROOT="/cygdrive/c/cygwin64/usr/i686-pc-cygwin/sys-root/"



clean:
	rm -f Console-Tank.exe

build: clean
	gcc -std=$(CCTAGS_STD)      \
		-o  $(OUTPUT_BIN)       \
		-lncursesw              \
			./src/draw_ncures.c \
			./src/body.c        \
			./src/bullet.c      \
			./src/bullet.c      \
			./src/tank.c        \
			./src/map.c         \
			./src/ui.c          \
			./src/boom.c        \
			./src/main.c


#	gcc -std=$(CCTAGS_STD) ./src/draw_ncures.c -lncursesw --sysroot=$(SYSROOT)
	gcc -std=$(CCTAGS_STD) ./src/body.c

#	gcc -std=$(CCTAGS_STD) src/*.c -lncursesw -o $(OUTPUT_BIN)  -print-sysroot

run: build
	$(OUTPUT_BIN)
