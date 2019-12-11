# Simple C Compiler

<br/>

## About

The Simple C Compiler project started as my final project for my Introduction to Programming Languages class at IUPUI (CSCI-35500).
However, the program for the class just implemented the C parser; it didn't implement the compiler which actually does semantic
analysis on the code. I'm currently working on finishing the rest of the program so I actually have a working C compiler, not just
a fancy C parser.

<br />

## Features to Still Implement

__Parsing:__
- [ ] Parse structs and unions
- [ ] Parse enumerations
- [ ] Parse initializer lists
- [ ] Parse `typedef` statements
- [ ] Complex and imaginary types (maybe?)

__Compiling:__
- [ ] Compile-time expression evaluation
- [ ] Runtime expression evaluation
- [ ] Local variables and scope resolution
- [ ] Integer promotion and type casting
- [ ] Function calls and stack frame
- [ ] Return values
- [ ] Goto statements and labels
- [ ] If statements
- [ ] While, do/while, and for loops
- [ ] Switch/case statements
- [ ] Const variables
- [ ] Bit fields (maybe?)

_These features are not listed in any particular order, and the list is not exhaustive._

<br />

## Compiling

The provided makefile should handle all of the compiling and linking of objects.
However, you will need to install the [Flex Lexer](https://www.gnu.org/software/flex/) and the
[Bison Parser](https://www.gnu.org/software/bison/), as SCC uses Flex and Bison to generate the
parser. For Debian Linux distributions, this is as simple as:
```
sudo apt-get install flex
sudo apt-get install bison
```

Once Flex and Bison are installed, simply type:
```
make
```
from the source directory, and everything should compile and link.
To rebuild the project from scratch, type:
```
make clean
make
```

<br/>

## Running

Usage:
```
./scc.out <c-file>
```

Right now, calling the parser with a C file will parse the file and print out the abstract syntax tree
to standard output. If there is an error parsing the C file (like invalid syntax), it will display a
"syntax error!" message.
