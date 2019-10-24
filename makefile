# Makefile for Insanity C Compiler
CC=g++
CFLAGS=-std=c++11 -Iinclude

PROGRAM=scc.out

OBJECTS=\
	parser/c.tab.o \
	parser/c.yy.o \
	scc.o \

# Add the source directory
OBJECTS := $(OBJECTS:%=src/%)



all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# Build the parser (using a Bison file)
%.tab.o: %.tab.cpp
%.tab.cpp: %.y
	bison --defines=$(@:%.cpp=%.h) -o $@ $<

# Build the lexer (using a Flex file)
%.yy.o: %.yy.cpp
%.yy.cpp: %.l
	flex --header-file=$(@:%.cpp=%.h) -o $@ $<



# Run the file
.PHONY: run
run: $(PROGRAM)
	./$(PROGRAM)

# Remove all files
.PHONY: clean
clean:
	rm -f $(PROGRAM) $(OBJECTS)
	rm -f src/parser/c.tab.cpp src/parser/c.yy.cpp
	rm -f src/parser/c.tab.h src/parser/c.yy.h
