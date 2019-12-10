# Simple C Compiler

<br/>

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

Calling the parser with a C file will parse the file and print out
the abstract syntax tree to standard output. If there is an error parsing
the C file (like invalid syntax), it will display a "syntax error!" message.
