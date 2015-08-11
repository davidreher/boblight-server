# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-c -Wall -std=c++11
LFLAGS=-lwiringPi -lboost_system -lboost_thread

all: boblight

boblight: main.o boblightServer.o ledController.o networkController.o
	$(CC) $(LFLAGS) main.o boblightServer.o ledController.o networkController.o -o boblight

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

boblightServer.o: boblightServer.cpp
	$(CC) $(CFLAGS) boblightServer.cpp

ledController.o: ledController.cpp
	$(CC) $(CFLAGS) ledController.cpp

networkController.o: networkController.cpp
	$(CC) $(CFLAGS) networkController.cpp
	

clean:
	rm -rf *o boblight
