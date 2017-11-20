GPP     = g++
CFLAGS  = -g -Wall -std=c++11
LINK	= -lncurses
RM      = rm -f
BINNAME = fwdre
SOURCE  = *.cpp Cutscenes/*.cpp FishingBoard/*.cpp Scenes/*.cpp Sleep/*.cpp Textbox/*.cpp

SHELL := /bin/bash

default: all

all: build

build: $(SOURCE)
	$(GPP) $(CFLAGS) -o $(BINNAME) $(SOURCE) $(LINK)

run: build
	./$(BINNAME)

#builds on top of deleted file
clean:
	$(RM) $(BINNAME)
	build
