GPP     = g++
CFLAGS  = -g -Wall -std=c++11
LINK	= -lncurses
RM      = rm -f
BINNAME = fwdre

SHELL := /bin/bash

default: all

all: build

build: *.cpp
	$(GPP) $(CFLAGS) -o $(BINNAME) $(LINK) *.cpp

run: build
	./$(BINNAME)

#builds on top of deleted file
clean:
	$(RM) $(BINNAME)
	bulid
