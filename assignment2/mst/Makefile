PROG := mst
SHELL := /bin/sh
CC := gcc
CXX := g++

#COMPILER_OPTIONS := -g -O0 -m64 -Wall -Wextra -Wshadow -Werror -pedantic
COMPILER_OPTIONS := -g -O0 -m64 -Wall -Wextra -Wshadow -Werror -pedantic
CFLAGS := -std=c99 $(COMPILER_OPTIONS)
CXXFLAGS := -std=c++0x -Weffc++ $(COMPILER_OPTIONS)
LDFLAGS := -Wl,--no-as-needed -lm

DEBUGFLAGS := #-g -O0 -D _DEBUG
RELEASEFLAGS := #-O2 -D NDEBUG

TARGET  := $(PROG)-test.x
SOURCES := $(shell echo *.cpp)
HEADERS := $(shell echo ./include/*.h)
#HEADERS = include/list.h
COMMON  :=
OBJECTS := $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(COMMON)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	-rm -f $(TARGET) $(OBJECTS) $(PROG).zip

%.o: %.c $(COMMON) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c -o $@ $<

.PHONY : all release
