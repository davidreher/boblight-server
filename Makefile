# use g++ as compiler
CC=g++
# show all warnings. Use c++11 as standard
CFLAGS=-c -Wall -std=c++11
# link with wiringPi, boost_system und boost_thread
LFLAGS=-lwiringPi -lboost_system -lboost_thread -pthread

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
