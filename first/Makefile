# CSC 453 Team 3
# Fall 2026 Dr. Wheat
#
# Template written by Josiah W
#
# to run: write "make first"

CWFLAGS = -Wextra -Wall

all:	firstTest

grammar.o:	grammar.h grammar.cpp
	g++ $(CWFLAGS) -O2 -c grammar.cpp -o grammar.o

symList.o:	grammar.h symList.h symList.cpp
	g++ $(CWFLAGS) -O2 -c symList.cpp -o symList.o

main.o:		grammar.h symList.h main.cpp
	g++ $(CWFLAGS) -O2 -c main.cpp -o main.o

first:		grammar.o main.o symList.o
	g++ $(CWFLAGS) -O2 grammar.o main.o symList.o -o first

clean:	
	rm -f *.o first first.exe


