# use g++ as compiler
CC = g++

# add debugging info and compiler warnings
CFLAGS = -c -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic 

ekg: ekg_simulator.o
	$(CC) ekg_simulator.o -o ekg_simulator

test_ekg: test_ekg.o 
	$(CC) test_ekg.o -o test_ekg

ekg_simulator.o: ekg_simulator.cpp
	$(CC) $(CFLAGS) ekg_simulator.cpp

test_ekg.o:
	$(CC) $(CFLAGS) test_ekg.cpp

clean:
	rm -f *.o ekg_simulator test_ekg