# Makefile for project

main:	*.h *.cpp
		g++ -g -Wall -o proj3 -std=c++11 *.cpp
clean:
	rm -f proj3
