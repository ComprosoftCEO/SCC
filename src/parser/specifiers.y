%define api.pure full
%name-prefix "specifiers_"
%locations

%parse-param { specifiers_t scanner } 
%lex-param { specifiers_t scanner }
%parse-param {DataType*& dt}

%code requires {

	#include <DataType.h>

	// Declare stuff from Flex that Bison needs to know about:
	typedef void* specifiers_t;
}

%code {
	// Let Bison know about tokenization methods
	static int specifiers_lex(YYSTYPE* yylvalp, YYLTYPE* yyllocp, specifiers_t scanner);
	static void specifiers_error(YYLTYPE* yyllocp, specifiers_t unused, DataType*& dt, const char* msg);
}


%token BOOL CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
// %token COMPLEX IMAGINARY 

%start data_type
%%

data_type
  : char
  | uchar
  | short
  | ushort
  | int
  | uint
  | long
  | ulong
  | longlong
  | ulonglong
  | float
  | double
  | longdouble
  ;

char
  : CHAR
  | SIGNED CHAR
  | CHAR SIGNED
  ;

uchar
  : UNSIGNED CHAR
  | CHAR UNSIGNED
  ;

short
  : SHORT
  | SIGNED SHORT
  | SHORT SIGNED
  | SHORT INT
  | SIGNED SHORT INT
  | SHORT SIGNED INT
  | SHORT INT SIGNED
  ;

ushort
  : UNSIGNED SHORT
  | SHORT UNSIGNED
  | UNSIGNED SHORT INT
  | SHORT UNSIGNED INT
  | SHORT INT UNSIGNED
  ;

int
  : INT
  | SIGNED
  | SIGNED INT
  | INT SIGNED
  ;

uint
  : UNSIGNED
  | UNSIGNED INT
  | INT UNSIGNED
  ;

long
  : LONG
  | SIGNED LONG
  | LONG SIGNED
  | LONG INT
  | SIGNED LONG INT
  | LONG SIGNED INT
  | LONG INT SIGNED
  ;

ulong
  : UNSIGNED LONG
  | LONG UNSIGNED
  | UNSIGNED LONG INT
  | LONG UNSIGNED INT
  | LONG INT UNSIGNED
  ;

longlong
  : LONG LONG
  | SIGNED LONG LONG
  | LONG SIGNED LONG
  | LONG LONG SIGNED
  | LONG LONG INT
  | SIGNED LONG LONG INT
  | LONG SIGNED LONG INT
  | LONG LONG SIGNED INT
  | LONG LONG INT SIGNED
  ;

ulonglong
  : UNSIGNED LONG LONG
  | LONG UNSIGNED LONG
  | LONG LONG UNSIGNED
  | UNSIGNED LONG LONG INT
  | LONG UNSIGNED LONG INT
  | LONG LONG UNSIGNED INT
  | LONG LONG INT UNSIGNED
  ;

float
  : FLOAT
  ;

double
  : DOUBLE
  ;

longdouble
  : LONG DOUBLE
  ;

%%


static int specifiers_lex(YYSTYPE* yylvalp, YYLTYPE* yyllocp, specifiers_t scanner) {
  // TODO: Implement this method
}

static void specifiers_error(YYLTYPE* yyllocp, specifiers_t unused, DataType*& output, const char *msg) {
	fprintf(stderr, "%s! [Line %d:%d]\n",
		msg,yyllocp->first_line, yyllocp->first_column);
}