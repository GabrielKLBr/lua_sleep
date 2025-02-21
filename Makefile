$(CC)=gcc
$(OBJ)=sleep.o
$(INPUT)=main.c
$(INCLUDE)=/path/to/include
$(LIBRARY)=/path/to/library

all: compile

compile:
	gcc -fPIC -c main.c -o sleep.o -IC:/Lua/include
	gcc -shared -fpic sleep.o -o sleep.dll -LC:/Lua/lib -llua54