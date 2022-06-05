SHELL = /bin/sh

SRCS := $(wildcard src/*.c)
PROGS = $(patsubst src/level%.c,level%,$(SRCS))

CFLAGS = -s -m32 -fno-stack-protector -O0 -w
CC = gcc


all: mkbin $(PROGS)

mkbin:
	@if [ ! -d bin ]; then mkdir bin; fi;

level5: src/level5.c
	$(CC) src/level5.c -o bin/level5 $(CFLAGS) -z execstack

level6_dump: src/level6_dump.c
	@echo "Skipped compiling level6_dump..."

%: src/%.c
	$(CC) $< -o bin/$@ $(CFLAGS)
	
