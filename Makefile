SHELL = /bin/sh

SRCS := $(wildcard src/*.c)
PROGS = $(patsubst src/%.c,%,$(SRCS))

CFLAGS = -s -m32 -fno-stack-protector -O0 -w
CC = gcc

all: $(PROGS)

%: src/%.c
	@if [ ! -d bin ]; then mkdir bin; fi;
	$(CC) $< -o bin/$@ $(CFLAGS)
	
