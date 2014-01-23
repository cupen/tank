OUTPUT_BIN=Console-Tank.exe
clean:
	rm -f Console-Tank.exe

build: clean
	gcc tank.c bullet.c lancher.c boom.c drawImp.c operateHitEvent.c -L lib -l pcc32 -o $(OUTPUT_BIN)
	
run: build
	$(OUTPUT_BIN)