# Makefile for Insanity C Compiler
CC=g++
CFLAGS=-std=c++11 -Iinclude

PROGRAM=scc.out

OBJECTS=\
	parser/c.tab.o \
	parser/c.yy.o \
	parser/specifiers.tab.o \
	expression/Expression.o \
	expression/UnaryExpression.o \
	expression/BinaryExpression.o \
	\
	Declarator.o \
	\
	factory/DataTypeFactory.o \
	factory/PointerFactory.o \
	factory/ArrayFactory.o \
	factory/FunctionFactory.o \
	scc.o \

# Add the source directory
OBJECTS := $(OBJECTS:%=src/%)
SOURCES := $(OBJECTS:%.o=%.cpp)



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



# Run the linters
# Add targets for linting the code
ALL_SOURCE_FILES = $(shell find ./ -regex '.*\.\(c\|cpp\|h\|hpp\)$$')

.PHONY: lint
lint: format tidy

.PHONY: format
format:
	clang-format -i -style=file $(ALL_SOURCE_FILES)

.PHONY: tidy
tidy:
	clang-tidy $(ALL_SOURCE_FILES) -config='' -fix-errors -- -Iinclude


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
