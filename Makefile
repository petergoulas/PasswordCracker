##Adapted from http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
##and https://stackoverflow.com/questions/18252734/using-o-files-in-makefile
##and workshops materials

CC=gcc
CFLAGS=-std=c99 -O3 -Wall -Wpedantic

##Create executable 
all: $(crack.c)
	gcc crack.c -o crack -std=c99 -O3 -Wall -Wpedantic
	
##clean
clean:
	rm -rf *.o crack
