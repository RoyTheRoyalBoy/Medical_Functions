# use g++ as compiler
CC = g++

# add debugging info and compiler warnings
CFLAGS = -c -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic 

all: ekg_simulator test_ekg test_ETCO2 test_display

ekg_simulator: ekg_simulator.o
	$(CC) ekg_simulator.o -o ekg_simulator

test_ekg: test_ekg.o
	$(CC) test_ekg.o -o test_ekg

test_display: test_display.o
	$(CC) test_display.o -o test_display

test_ETCO2:  test_ETCO2.o
	$(CC) test_ETCO2.o -o test_ETCO2

ekg_simulator.o: ekg_simulator.cpp
	$(CC) $(CFLAGS) ekg_simulator.cpp

display.o: display.cpp
	$(CC) $(CFLAGS) display.cpp

test_ekg.o:
	$(CC) $(CFLAGS) test_ekg.cpp

test_display.o:
	$(CC) $(CFLAGS) test_display.cpp

test_ETCO2.o:
	$(CC) $(CFLAGS) test_ETCO2.cpp

clean:
	rm -f *.o ekg_simulator test_ekg test_display test_ETCO2