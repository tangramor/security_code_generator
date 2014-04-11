# This is the Makefile
CC = gcc
CFLAGS = -DDEBUG -c
#LIBS = -lncurses
#INCLUDE = -I/usr/src/include

all: clean codegen

install:
	
codegen: code_generator.c uuid.c sysdep.c md5c.c
	$(CC) -o $@ $? 
	
uuidtest: utest.c uuid.c sysdep.c md5c.c
	$(CC) -o $@ $? 
#$(LIBS)
#utils.o:
#        $(CC) $(CFLAGS) -o $@ utils.c $(INCLUDE)
clean:
	-rm codegen

