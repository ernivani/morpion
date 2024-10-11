CC = gcc
INCLUDES = -Iinclude
CFLAGS = -Wall -Wextra -O2
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LIBS = $(shell sdl2-config --libs)
THREADS_LIBS = -pthread
Math_LIBS = -lm

SRCDIR = src

SRCS = $(wildcard $(SRCDIR)/*.c)


all: client

client: 
	$(CC) $(CFLAGS) $(SDL2_CFLAGS) -g -o main $(SRCS) $(INCLUDES) $(SDL2_LIBS) $(THREADS_LIBS) $(Math_LIBS)

clean:
	rm -f client server

