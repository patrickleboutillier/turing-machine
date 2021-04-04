GCC_ARGS = -g -O0 -Wno-return-type 
LIBS = -lstdc++
SOURCE = TAPE.cpp MCONFIG.cpp MF.cpp MACHINE.cpp MFUNCTIONS.cpp

clean:
	rm -f t main out
	 
build: 
	g++ $(GCC_ARGS) $(SOURCE) $(LIBS) main.cpp -o main


test: 
	@g++ $(GCC_ARGS) $(SOURCE) $(LIBS) test.cpp -o t
	@./t $(STEPS)
