# CSC 453 Team 3
# Fall 2026 Dr. Wheat
#
# Template written by Josiah W

CWFLAGS = -Wextra -Wall

all:	firstTest

symList.o:	global.h symList.h symList.cpp
	g++ $(CWFLAGS) -O2 -c symList.cpp -o symList.o

first.o:	global.h first.h symList.h first.cpp 
	g++ $(CWFLAGS) -O2 -c first.cpp -o first.o

main.o:		global.h first.h symList.h main.cpp
	g++ $(CWFLAGS) -O2 -c main.cpp -o main.o

firstTest:	global.h main.o first.o symList.o
	g++ $(CWFLAGS) -O2 main.o first.o symList.o -o firstTest

clean:	
	rm -f *.o firstTest firstTest.exe


