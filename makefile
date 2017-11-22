SOURCES = ac.c gotoBuild.c input.c failureBuild.c 
OBJECTS = ac.o gotoBuild.o input.o failureBuild.c 
HEADERS = ac.h
CC = gcc
CFLAGS = -g -Wall

AhoCorasick: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o ac
clean:
	rm -fR *o AhoCorasick
	rm ac
