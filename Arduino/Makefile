GCC_ARGS = -IMachines -Wno-return-type -lstdc++
SOURCE = TAPE.cpp MCONFIG.cpp MACHINE.cpp MFUNCTIONS.cpp


build: 
	gcc $(GCC_ARGS) $(SOURCE) main.cpp -o main


test: 
	@gcc $(GCC_ARGS) $(SOURCE) test.cpp -o t
	@./t
