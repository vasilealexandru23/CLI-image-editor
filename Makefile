# Copyright 2023 Vasile Alexandru-Gabriel <vasilealexandru37@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99 

# define targets
TARGETS=image_editor

build:
	$(CC) $(CFLAGS) *.c *.h -o image_editor -lm

pack:
	zip -FSr 314CA_VasileAlexandruGabriel_Tema3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean