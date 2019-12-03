# Makefile for Insanity C Compiler
CC=g++
CFLAGS=-std=c++11 -Iinclude -g

PROGRAM=scc.out

OBJECTS=\
	parser/c.tab.o \
	parser/c.yy.o \
	parser/specifiers.tab.o \
	\
  datatype/CTypes.o \
	datatype/DataType.o \
	datatype/PrimitiveDataType.o \
	datatype/VoidDataType.o \
	datatype/CharDataType.o \
	datatype/UnsignedCharDataType.o \
	datatype/ShortDataType.o \
	datatype/UnsignedShortDataType.o \
	datatype/IntDataType.o \
	datatype/UnsignedIntDataType.o \
	datatype/LongDataType.o \
	datatype/UnsignedLongDataType.o \
	datatype/LongLongDataType.o \
	datatype/UnsignedLongLongDataType.o \
	datatype/FloatDataType.o \
	datatype/DoubleDataType.o \
	datatype/LongDoubleDataType.o \
	datatype/PointerDataType.o \
	datatype/ArrayDataType.o \
	datatype/FunctionDataType.o \
	\
	expression/Expression.o \
	expression/CommaExpression.o \
	expression/AssignmentExpression.o \
	expression/CastExpression.o \
	expression/ConstantExpression.o \
	expression/StringExpression.o \
	expression/IdentifierExpression.o \
	expression/BracketExpression.o \
	expression/FunctionCallExpression.o \
	expression/UnaryExpression.o \
	expression/MinusExpression.o \
	expression/NotExpression.o \
	expression/ComplementExpression.o \
	expression/DereferenceExpression.o \
	expression/AddressOfExpression.o \
	expression/SizeofExpression.o \
	expression/AlignofExpression.o \
	expression/BinaryExpression.o \
	expression/AdditionExpression.o \
	expression/SubtractionExpression.o \
	expression/MultiplicationExpression.o \
	expression/DivisionExpression.o \
	expression/ModulusExpression.o \
	expression/LeftShiftExpression.o \
	expression/RightShiftExpression.o \
	expression/LessThanExpression.o \
	expression/GreaterThanExpression.o \
	expression/LessThanOrEqualExpression.o \
	expression/GreaterThanOrEqualExpression.o \
	expression/EqualsExpression.o \
	expression/NotEqualsExpression.o \
	expression/BitwiseAndExpression.o \
	expression/BitwiseOrExpression.o \
	expression/BitwiseXorExpression.o \
	expression/LogicalAndExpression.o \
	expression/LogicalOrExpression.o \
	expression/ConditionalExpression.o \
	\
	statement/Statement.o \
	statement/EmptyStatement.o \
	statement/DeclarationStatement.o \
	statement/LabelStatement.o \
	statement/CaseStatement.o \
	statement/DefaultCaseStatement.o \
	statement/CompoundStatement.o \
	statement/ExpressionStatement.o \
	statement/IfStatement.o \
	statement/SwitchStatement.o \
	statement/GotoStatement.o \
	statement/WhileStatement.o \
	statement/DoWhileStatement.o \
	statement/ForStatement.o \
	statement/ContinueStatement.o \
	statement/BreakStatement.o \
	statement/ReturnStatement.o \
	\
	visitor/ExpressionVisitor.o \
	visitor/StatementVisitor.o \
	visitor/DataTypeVisitor.o \
	visitor/PrintDataType.o \
	\
	declaration/Declaration.o \
	declaration/Declarator.o \
	declaration/Parameter.o \
	declaration/FunctionDefinition.o \
	declaration/SpecifierQualifierBuilder.o \
	\
	factory/DataTypeFactory.o \
	factory/PointerFactory.o \
	factory/ArrayFactory.o \
	factory/FunctionFactory.o \
	\
	TranslationUnit.o \
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
	bison --defines=$(@:%.cpp=%.h) -o $@ $< -v

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
	rm -f src/parser/c.tab.cpp src/parser/c.yy.cpp src/parser/c.output
	rm -f src/parser/c.tab.h src/parser/c.yy.h
