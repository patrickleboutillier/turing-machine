GCC_ARGS = -IMachines -Wno-return-type 
LIBS = -lstdc++
SOURCE = TAPE.cpp MCONFIG.cpp MACHINE.cpp MFUNCTIONS.cpp


build: 
	g++ $(GCC_ARGS) $(SOURCE) $(LIBS) main.cpp -o main


test: 
	@g++ $(GCC_ARGS) $(SOURCE) $(LIBS) test.cpp -o t
	@time ./t $(STEPS)
