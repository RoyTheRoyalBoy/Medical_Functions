# use g++ as compiler
CC = g++

# add debugging info and compiler warnings
CFLAGS = -c -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic 

test: test*.o functions.o
	$(CC) test*.o functions.o -o test

functions.o: functions.cpp
	$(CC) $(CFLAGS) functions.cpp

test.o:
	$(CC) $(CFLAGS) $(wildcard test*.cpp)

clean:
	rm -f *.o functions test