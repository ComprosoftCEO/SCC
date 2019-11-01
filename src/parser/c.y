%define api.pure full
%name-prefix "cc"
%locations

%parse-param { yyscan_t scanner } 
%lex-param { yyscan_t scanner }
// %parse-param {InsanityProgram* program}

%code requires {
  #include <cstdio>
  #include <cstdlib>
  #include <string>

  #include <DataType.h>
  #include <DataTypeFactory.h>
  #include <Declarator.h>
  #include <Expression.h>

  // Declare stuff from Flex that Bison needs to know about:
  typedef void* yyscan_t;
}

%code {
  // Let Bison know about Flex methods
  int cclex(YYSTYPE* yylvalp, YYLTYPE* yyllocp, yyscan_t scanner);
  static void ccerror(YYLTYPE* yyllocp, yyscan_t unused /*, InsanityProgram* program*/, const char* msg);
}


%union {
  C_INT ival;          // Literal integer
  C_UINT uival;        // Literal unsigned integer
  C_LONG lval;         // Literal long
  C_ULONG ulval;       // Literal unsigned long
  C_LONGLONG llval;    // Literal long long
  C_ULONGLONG ullval;  // Literal unsigned long long
  C_FLOAT fval;        // Literal floating point
  C_DOUBLE dval;       // Literal double

  std::string* str;                     // Identifier, string, type, etc.
  Expression* expr;                     // Expression interface
  DataType* dt;                         // Data type object
  Declarator* decl;                     // Declarator type (builds data type)
  DataTypeFactory* fact;                // Abstract factory type
  std::vector<Expression*>* expr_list;  // List of expressions
  ParameterList* param_list;            // List of parameters
}

//Destructors
%destructor {delete($$);} <expr> <str>
%destructor {delete($$);} <dt> <decl> <fact>
%destructor {
  for (auto el : *($$)) {
    delete(el);
  }
  delete($$);
} <expr_list>


//Terminal types
%token <str> IDENTIFIER STRING_LITERAL FUNC_NAME TYPEDEF_NAME ENUMERATION_CONSTANT

%token <ival> INT_CONSTANT
%token <uival> UINT_CONSTANT
%token <lval> LONG_CONSTANT LONGLONG_CONSTANT
%token <ulval> ULONG_CONSTANT ULONGLONG_CONSTANT
%token <fval> F_CONSTANT
%token <dval> D_CONSTANT

%token SIZEOF
%token PTR_OP "->"
%token INC_OP "++"
%token DEC_OP "--"
%token LEFT_OP "<<" 
%token RIGHT_OP ">>"
%token LE_OP "<="
%token GE_OP ">="
%token EQ_OP "=="
%token NE_OP "!="

%token AND_OP "&&"
%token OR_OP "||"

%token MUL_ASSIGN "*="
%token DIV_ASSIGN "/="
%token MOD_ASSIGN "%="
%token ADD_ASSIGN "+="
%token SUB_ASSIGN "-="
%token LEFT_ASSIGN "<<="
%token RIGHT_ASSIGN ">>="
%token AND_ASSIGN "&="
%token XOR_ASSIGN "^="
%token OR_ASSIGN "|="

%token TYPEDEF EXTERN STATIC AUTO REGISTER INLINE
%token CONST RESTRICT VOLATILE
%token BOOL CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token COMPLEX IMAGINARY 
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN
%token ALIGNAS ALIGNOF ATOMIC GENERIC NORETURN STATIC_ASSERT THREAD_LOCAL


//Nonterminal types

%type <str> string

// Expressions
%type <expr> primary_expression postfix_expression unary_expression cast_expression
%type <expr> multiplicative_expression additive_expression shift_expression
%type <expr> relational_expression equality_expression
%type <expr> and_expression exclusive_or_expression inclusive_or_expression
%type <expr> logical_and_expression logical_or_expression conditional_expression
%type <expr> assignment_expression expression constant_expression
%type <expr_list> argument_expression_list

// Data types
%type <dt> specifier_qualifier_list type_name

// Declarators
%type <decl> declarator direct_declarator
%type <fact> pointer
%type <fact> abstract_declarator direct_abstract_declarator

// Parameters
%type <param> parameter_declaration
%type <param_list> parameter_list

//%type <list> insanity if
//%type <stmt> statement
//%type <label> lblName label jump subroutine libraryLabel libraryCall

%start translation_unit
%%

primary_expression
  : IDENTIFIER          { $$ = new IdentifierExpression(*$1); delete($1); }
  | constant            { $$ = nullptr; /* TODO: Implement constants */ }
  | string              { $$ = nullptr;  /* TODO: Implement this */}
  | '(' expression ')'  { $$ = $2; }
  ;

constant
  : INT_CONSTANT    /* includes character_constant */
  | UINT_CONSTANT
  | LONG_CONSTANT
  | ULONG_CONSTANT
  | LONGLONG_CONSTANT
  | ULONGLONG_CONSTANT
  | F_CONSTANT
  | D_CONSTANT
  // | ENUMERATION_CONSTANT  /* after it has been defined as such */
  ;

// enumeration_constant    /* before it has been defined as such */
//   : IDENTIFIER
//   ;

string
  : STRING_LITERAL
  // | FUNC_NAME
  ;

postfix_expression
  : primary_expression                                    { $$ = $1; }
  | postfix_expression '[' expression ']'                  { $$ = new BracketExpression($1, $3); }
  | postfix_expression '(' ')'                            { $$ = new FunctionCallExpression($1); }
  | postfix_expression '(' argument_expression_list ')'   { $$ = new FunctionCallExpression($1, *$3); }
  // | postfix_expression '.' IDENTIFIER
  // | postfix_expression "->" IDENTIFIER
  // | postfix_expression "++"
  // | postfix_expression "--"
  // | '(' type_name ')' '{' initializer_list '}'
  // | '(' type_name ')' '{' initializer_list ',' '}'
  ;

argument_expression_list
  : assignment_expression                               { $$ = new std::vector<Expression*>{$1}; }
  | argument_expression_list ',' assignment_expression  { $$ = $1; $1->push_back($3); }
  ;

unary_expression
  : postfix_expression          { $$ = $1; }
  // | "++" unary_expression
  // | "--" unary_expression
  | '&' cast_expression         { $$ = new AddressOfExpression($2); }
  | '*' cast_expression         { $$ = new DereferenceExpression($2); }
  | '+' cast_expression         { $$ = $2; /* TODO: Upcast to integer */ }
  | '-' cast_expression         { $$ = new MinusExpression($2); }
  | '~' cast_expression         { $$ = new ComplementExpression($2); }
  | '!' cast_expression         { $$ = new NotExpression($2); }
  | SIZEOF unary_expression     { $$ = new SizeofExpression($2); }
  // | SIZEOF '(' type_name ')'    { $$ = new SizeofExpression($3); }
  // | ALIGNOF '(' type_name ')'   { $$ = new AlignofExpression($3); }
  ;

cast_expression
  : unary_expression                    { $$ = $1; }
  | '(' type_name ')' cast_expression   { $$ = $4; /* TODO: Cast expression */}
  ;

multiplicative_expression
  : cast_expression                                 { $$ = $1; }
  | multiplicative_expression '*' cast_expression   { $$ = new MultiplicationExpression($1, $3); }
  | multiplicative_expression '/' cast_expression   { $$ = new DivisionExpression($1, $3); }
  | multiplicative_expression '%' cast_expression   { $$ = new ModulusExpression($1, $3); }
  ;

additive_expression
  : multiplicative_expression                           { $$ = $1; }
  | additive_expression '+' multiplicative_expression   { $$ = new AdditionExpression($1, $3); }
  | additive_expression '-' multiplicative_expression   { $$ = new SubtractionExpression($1, $3); }
  ;

shift_expression
  : additive_expression                         { $$ = $1; }
  | shift_expression "<<" additive_expression   { $$ = new LeftShiftExpression($1, $3); }
  | shift_expression ">>" additive_expression   { $$ = new RightShiftExpression($1, $3); }
  ;

relational_expression
  : shift_expression                              { $$ = $1; }
  | relational_expression '<' shift_expression    { $$ = new LessThanExpression($1, $3); }
  | relational_expression '>' shift_expression    { $$ = new GreaterThanExpression($1, $3); }
  | relational_expression "<=" shift_expression   { $$ = new LessThanOrEqualExpression($1, $3); }
  | relational_expression ">=" shift_expression   { $$ = new GreaterThanOrEqualExpression($1, $3); }
  ;

equality_expression
  : relational_expression                           { $$ = $1; }
  | equality_expression "==" relational_expression  { $$ = new EqualsExpression($1, $3); }
  | equality_expression "!=" relational_expression  { $$ = new NotEqualsExpression($1, $3); }
  ;

and_expression
  : equality_expression                     { $$ = $1; }
  | and_expression '&' equality_expression  { $$ = new BitwiseAndExpression($1, $3); }
  ;

exclusive_or_expression
  : and_expression                              { $$ = $1; }
  | exclusive_or_expression '^' and_expression  { $$ = new BitwiseXorExpression($1, $3); }
  ;

inclusive_or_expression
  : exclusive_or_expression                               { $$ = $1; }
  | inclusive_or_expression '|' exclusive_or_expression   { $$ = new BitwiseOrExpression($1, $3); }
  ;

logical_and_expression
  : inclusive_or_expression                               { $$ = $1; }
  | logical_and_expression "&&" inclusive_or_expression   { $$ = new LogicalAndExpression($1, $3); }
  ;

logical_or_expression
  : logical_and_expression                              { $$ = $1; }
  | logical_or_expression "||" logical_and_expression   { $$ = new LogicalOrExpression($1, $3); }
  ;

conditional_expression
  : logical_or_expression                                             { $$ = $1; }
  | logical_or_expression '?' expression ':' conditional_expression   { $$ = new ConditionalExpression($1, $3, $5); }
  ;

assignment_expression
  : conditional_expression                        { $$ = $1; }
  | unary_expression '=' assignment_expression    { $$ = new AssignmentExpression($1, $3); }
  // | unary_expression "*=" assignment_expression
  // | unary_expression "/=" assignment_expression
  // | unary_expression "%=" assignment_expression
  // | unary_expression "+=" assignment_expression
  // | unary_expression "-=" assignment_expression
  // | unary_expression "<<=" assignment_expression
  // | unary_expression ">>=" assignment_expression
  // | unary_expression "&=" assignment_expression
  // | unary_expression "^=" assignment_expression
  // | unary_expression "|=" assignment_expression
  ;

expression
  : assignment_expression                 { $$ = new CommaExpression(); ((CommaExpression*) $$)->add_expression($1); }
  | expression ',' assignment_expression  { $$ = $1; ((CommaExpression*) $$)->add_expression($3); }
  ;

constant_expression
  : conditional_expression  { $$ = $1; /* with constraints */ }
  ;

declaration
  : declaration_specifiers ';'
  | declaration_specifiers init_declarator_list ';'
  | TYPEDEF declaration_specifiers ';'
  | TYPEDEF declaration_specifiers declarator_list ';'
  ;

declaration_specifiers
  : storage_class_specifier declaration_specifiers
  | storage_class_specifier
  | type_specifier declaration_specifiers
  | type_specifier
  | type_qualifier declaration_specifiers
  | type_qualifier
  | function_specifier declaration_specifiers
  | function_specifier
  // | alignment_specifier declaration_specifiers
  // | alignment_specifier
  ;

init_declarator_list
  : init_declarator
  | init_declarator_list ',' init_declarator
  ;

init_declarator
  : declarator '=' initializer
  | declarator
  ;

declarator_list
  : declarator
  | declarator_list ',' declarator
  ;

storage_class_specifier
  : EXTERN
  | STATIC
  | THREAD_LOCAL
  | AUTO
  | REGISTER
  ;

type_specifier
  : VOID
  | CHAR
  | SHORT
  | INT
  | LONG
  | FLOAT
  | DOUBLE
  | SIGNED
  | UNSIGNED
  | BOOL
  // | COMPLEX
  // | IMAGINARY      /* non-mandated extension */
  // | atomic_type_specifier
  // | struct_or_union_specifier
  // | enum_specifier
  // | TYPEDEF_NAME    /* after it has been defined as such */
  ;

// struct_or_union_specifier
//   : struct_or_union '{' struct_declaration_list '}'
//   | struct_or_union IDENTIFIER '{' struct_declaration_list '}'
//   | struct_or_union IDENTIFIER
//   ;

// struct_or_union
//   : STRUCT
//   | UNION
//   ;

// struct_declaration_list
//   : struct_declaration
//   | struct_declaration_list struct_declaration
//   ;

// struct_declaration
//   : specifier_qualifier_list ';'  /* for anonymous struct/union */
//   | specifier_qualifier_list struct_declarator_list ';'
//   ;

specifier_qualifier_list
  : type_specifier specifier_qualifier_list
  | type_specifier
  | type_qualifier specifier_qualifier_list
  | type_qualifier
  ;

// struct_declarator_list
//   : struct_declarator
//   | struct_declarator_list ',' struct_declarator
//   ;

// struct_declarator
//   : ':' constant_expression
//   | declarator ':' constant_expression
//   | declarator
//   ;

// enum_specifier
//   : ENUM '{' enumerator_list '}'
//   | ENUM '{' enumerator_list ',' '}'
//   | ENUM IDENTIFIER '{' enumerator_list '}'
//   | ENUM IDENTIFIER '{' enumerator_list ',' '}'
//   | ENUM IDENTIFIER
//   ;

// enumerator_list
//   : enumerator
//   | enumerator_list ',' enumerator
//   ;

// enumerator  /* identifiers must be flagged as ENUMERATION_CONSTANT */
//   : enumeration_constant '=' constant_expression
//   | enumeration_constant
//   ;

// atomic_type_specifier
//   : ATOMIC '(' type_name ')'
//   ;

type_qualifier
  : CONST
  | RESTRICT
  | VOLATILE
  | ATOMIC
  ;

function_specifier
  : INLINE
  | NORETURN
  ;

// alignment_specifier
//   : ALIGNAS '(' type_name ')'
//   | ALIGNAS '(' constant_expression ')'
//   ;

declarator
  : pointer direct_declarator
  | direct_declarator
  ;

direct_declarator
  : IDENTIFIER
  | '(' declarator ')'
  | direct_declarator '[' ']'
  | direct_declarator '[' type_qualifier_list assignment_expression ']'
  | direct_declarator '[' type_qualifier_list ']'
  | direct_declarator '[' assignment_expression ']'
  | direct_declarator '(' parameter_type_list ')'
  | direct_declarator '(' ')'
  ;

pointer
  : '*' type_qualifier_list pointer
  | '*' type_qualifier_list
  | '*' pointer
  | '*'
  ;

type_qualifier_list
  : type_qualifier
  | type_qualifier_list type_qualifier
  ;

parameter_type_list
  : parameter_list ',' ELLIPSIS
  | parameter_list
  ;

parameter_list
  : parameter_declaration
  | parameter_list ',' parameter_declaration
  ;

parameter_declaration
  : declaration_specifiers declarator
  | declaration_specifiers abstract_declarator
  | declaration_specifiers
  ;

type_name
  : specifier_qualifier_list abstract_declarator
  | specifier_qualifier_list
  ;

abstract_declarator
  : pointer direct_abstract_declarator
  | pointer
  | direct_abstract_declarator
  ;

direct_abstract_declarator
  : '(' abstract_declarator ')'
  | '[' ']'
  | '[' type_qualifier_list assignment_expression ']'
  | '[' type_qualifier_list ']'
  | '[' assignment_expression ']'
  | direct_abstract_declarator '[' ']'
  | direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
  | direct_abstract_declarator '[' type_qualifier_list ']'
  | direct_abstract_declarator '[' assignment_expression ']'
  | '(' ')'
  | '(' parameter_type_list ')'
  | direct_abstract_declarator '(' ')'
  | direct_abstract_declarator '(' parameter_type_list ')'
  ;

initializer
  // : '{' initializer_list '}'
  // | '{' initializer_list ',' '}'
  : assignment_expression
  ;

// initializer_list
//   : designation initializer
//   | initializer
//   | initializer_list ',' designation initializer
//   | initializer_list ',' initializer
//   ;

// designation
//   : designator_list '='
//   ;

// designator_list
//   : designator
//   | designator_list designator
//   ;

// designator
//   : '[' constant_expression ']'
//   | '.' IDENTIFIER
//   ;

function_declarator
  : pointer direct_function_declarator
  | direct_function_declarator
  ;

direct_function_declarator
  : IDENTIFIER '(' ')'
  | IDENTIFIER '(' VOID ')'
  | IDENTIFIER '(' named_parameter_type_list ')'
  | '(' function_declarator ')'
  | direct_function_declarator'[' ']'
  | direct_function_declarator '[' type_qualifier_list assignment_expression ']'
  | direct_function_declarator '[' type_qualifier_list ']'
  | direct_function_declarator '[' assignment_expression ']'
  | direct_function_declarator '(' parameter_type_list ')'
  | direct_function_declarator '(' ')'
  ;

named_parameter_type_list
  : named_parameter_list ',' ELLIPSIS
  | named_parameter_list
  ;

named_parameter_list
  : named_parameter_declaration
  | named_parameter_list ',' named_parameter_declaration
  ;

named_parameter_declaration
  : declaration_specifiers declarator
  ;

statement
  : labeled_statement
  | compound_statement
  | expression_statement
  | selection_statement
  | iteration_statement
  | jump_statement
  ;

labeled_statement
  : IDENTIFIER ':' statement
  | CASE constant_expression ':' statement
  | DEFAULT ':' statement
  ;

compound_statement
  : '{' '}'
  | '{'  block_item_list '}'
  ;

block_item_list
  : block_item
  | block_item_list block_item
  ;

block_item
  : declaration
  | statement
  ;

expression_statement
  : ';'
  | expression ';'
  ;

selection_statement
  : IF '(' expression ')' statement ELSE statement
  | IF '(' expression ')' statement
  | SWITCH '(' expression ')' statement
  ;

iteration_statement
  : WHILE '(' expression ')' statement
  | DO statement WHILE '(' expression ')' ';'
  | FOR '(' expression_statement expression_statement ')' statement
  | FOR '(' expression_statement expression_statement expression ')' statement
  | FOR '(' declaration expression_statement ')' statement
  | FOR '(' declaration expression_statement expression ')' statement
  ;

jump_statement
  : GOTO IDENTIFIER ';'
  | CONTINUE ';'
  | BREAK ';'
  | RETURN ';'
  | RETURN expression ';'
  ;

translation_unit
  : external_declaration
  | translation_unit external_declaration
  ;

external_declaration
  : function_definition
  | declaration
  ;

function_definition
  : declaration_specifiers function_declarator compound_statement
  ;

/* We aren't supporting the K&R syntax */

%%


static void ccerror(YYLTYPE* yyllocp, yyscan_t unused /*, InsanityProgram* program */, const char *msg) {
  fprintf(stderr, "%s! [Line %d:%d]\n",
    msg,yyllocp->first_line, yyllocp->first_column);
}
