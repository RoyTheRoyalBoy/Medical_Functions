# use g++ as compiler
CC = g++

# add debugging info and compiler warnings
CFLAGS = -c -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic 


test_EKG: test_EKG.o EKG_simulator.o
	$(CC) test_EKG.o EKG_simulator.o -o test_EKG

EKG_simulator.o: EKG_simulator.cpp
	$(CC) $(CFLAGS) EKG_simulator.cpp

test_EKG.o:
	$(CC) $(CFLAGS) test_EKG.cpp

clean:
	rm -f *.o EKG_simulator test_EKG