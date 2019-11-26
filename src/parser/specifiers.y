%define api.pure full
%name-prefix "specifiers_"

%parse-param { TypeSpecifierList& specifiers } 
%lex-param { TypeSpecifierList& specifiers }
%parse-param { DataType*& dt }

%code requires {
	#include <DataType.h>
  #include <Declaration.h>
}

%code {
	// Let Bison know about tokenization methods
	extern int specifiers_lex(YYSTYPE* yylvalp, TypeSpecifierList& specifiers);
	static void specifiers_error(TypeSpecifierList& unused, DataType*& dt, const char* msg);
}


%token VOID CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE BOOL
// %token COMPLEX IMAGINARY 

%start data_type
%%

data_type
  : void        { dt = new VoidDataType(); }
  | char        { dt = new CharDataType(); }
  | uchar       { dt = new UnsignedCharDataType(); }
  | short       { dt = new ShortDataType(); }
  | ushort      { dt = new UnsignedShortDataType(); }
  | int         { dt = new IntDataType(); }
  | uint        { dt = new UnsignedIntDataType(); }
  | long        { dt = new LongDataType(); }
  | ulong       { dt = new UnsignedLongDataType(); }
  | longlong    { dt = new LongLongDataType(); }
  | ulonglong   { dt = new UnsignedLongLongDataType(); }
  | float       { dt = new FloatDataType(); }
  | double      { dt = new DoubleDataType(); }
  | longdouble  { dt = new LongDoubleDataType(); }
  ;

void
  : VOID
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

static void specifiers_error(TypeSpecifierList& unused, DataType*& output, const char *msg) {
	fprintf(stderr, "Invalid type specifier: %s!\n", msg);
}