# use g++ as compiler
CC = g++

# add debugging info and compiler warnings
CFLAGS = -c -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic 

all: EKG_simulator ETCO2_simulator display test_EKG test_ETCO2 test_display

EKG_simulator: EKG_simulator.o
	$(CC) EKG_simulator.o -o EKG_simulator

ETCO2_simulator: ETCO2_simulator.o
	$(CC) ETCO2_simulator.o -o ETCO2_simulator

display: display.o
	$(CC) display.o -o display

test_EKG: test_EKG.o
	$(CC) test_EKG.o -o test_EKG

test_display: test_display.o
	$(CC) test_display.o -o test_display

test_ETCO2:  test_ETCO2.o
	$(CC) test_ETCO2.o -o test_ETCO2

EKG_simulator.o: EKG_simulator.cpp
	$(CC) $(CFLAGS) EKG_simulator.cpp

ETCO2_simulator.o: ETCO2_simulator.cpp
	$(CC) $(CFLAGS) ETCO2_simulator.cpp

display.o: display.cpp
	$(CC) $(CFLAGS) display.cpp

test_EKG.o:
	$(CC) $(CFLAGS) test_EKG.cpp

test_display.o:
	$(CC) $(CFLAGS) test_display.cpp

test_ETCO2.o:
	$(CC) $(CFLAGS) test_ETCO2.cpp

clean:
	rm -f *.o EKG_simulator ETCO2_simulator display test_EKG test_display test_ETCO2