# Makefile for project

main:	*.h *.cpp
		g++ -g -Wall -o proj4 -std=c++11 *.cpp
clean:
	rm -f proj4
