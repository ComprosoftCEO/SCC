%define api.pure full
%name-prefix "cc"
%locations

%parse-param { yyscan_t scanner } 
%lex-param { yyscan_t scanner }
%parse-param { FunctionDefinitionList& functions }

%code requires {
  #include <cstdio>
  #include <cstdlib>
  #include <string>

  #include <DataType.h>
  #include <DataTypeFactory.h>
  #include <Declaration.h>
  #include <Expression.h>
  #include <FunctionDefinition.h>
  #include <Parameter.h>
  #include <Statement.h>

  // Declare stuff from Flex that Bison needs to know about:
  typedef void* yyscan_t;
}

%code {
  // Let Bison know about Flex methods
  int cclex(YYSTYPE* yylvalp, YYLTYPE* yyllocp, yyscan_t scanner);
  static void ccerror(YYLTYPE* yyllocp, yyscan_t unused, FunctionDefinitionList& functions, const char *msg);
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
  std::vector<Expression*>* expr_list;  // List of expressions
  Statement* stmt;                      // Statement type
  StatementList* stmt_list;             // List of statements
  DataType* dt;                         // Data type object

  DeclarationList* decl_list;           // List of declarations with a name
  Declaration* decl;                    // Declaration (one with a name)
  DeclaratorList* declr_list;           // List of declarators
  Declarator* declr;                    // Declarator type (builds data type)
  DataTypeFactory* fact;                // Abstract factory type
  PointerFactory* pfact;                // Pointer factory (special case)

  Parameter* param;                     // Single parameter in a function
  ParameterList* param_list;            // List of parameters in a function
  FunctionDefinition* func;             // Single function definition
  FunctionDefinitionList* func_list;    // List of function definitions
}

//Destructors
%destructor {delete($$);} <str> <expr> <dt> <stmt>
%destructor {delete($$);} <decl> <declr> <fact> <pfact>
%destructor {delete($$);} <param> <param_list> <func>
%destructor {
  for (auto el : *($$)) {
    delete(el);
  }
  delete($$);
} <expr_list> <decl_list> <declr_list> <stmt_list> <func_list>


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

// Declarations and declarators
%type <decl_list> declaration
%type <dt> declaration_specifiers specifier_qualifier_list type_specifier
%type <declr_list> init_declarator_list declarator_list
%type <declr> init_declarator declarator direct_declarator
%type <dt> type_name
%type <fact> abstract_declarator direct_abstract_declarator
%type <expr> initializer
%type <pfact> pointer

// Parameters
%type <param_list> parameter_list
%type <param> parameter_declaration

// Statements
%type <stmt> statement
%type <expr> expression_statement
%type <stmt> labeled_statement compound_statement selection_statement iteration_statement jump_statement
%type <stmt_list> block_item block_item_list

// Function definition
%type <func> function_definition
%type <func_list> function_definition_list

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
  | postfix_expression '[' expression ']'                 { $$ = new BracketExpression($1, $3); }
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
  | '(' type_name ')' cast_expression   { $$ = new CastExpression($4, $2); }
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
  : declaration_specifiers init_declarator_list ';'   {
    $$ = new DeclarationList();
    for (auto decl : *$2) {
      $$->push_back(decl->build_declaration($1->clone()));
      delete(decl);
    }
    delete($2);
    delete($1);
  }
  ;

typedef_declaration
  : TYPEDEF declaration_specifiers declarator_list
  ;

declaration_specifiers
  : type_specifier      { $$ = $1; }
  // : storage_class_specifier declaration_specifiers
  // | storage_class_specifier
  // | type_specifier declaration_specifiers
  // | type_specifier
  // | type_qualifier declaration_specifiers
  // | type_qualifier
  // | function_specifier declaration_specifiers
  // | function_specifier
  // | alignment_specifier declaration_specifiers
  // | alignment_specifier
  ;

init_declarator_list
  : init_declarator                           { $$ = new DeclaratorList{$1}; }
  | init_declarator_list ',' init_declarator  { $$ = $1; $1->push_back($3); }
  ;

init_declarator
  : declarator '=' initializer  { $$ = $1; $1->set_initializer($3); }
  | declarator                  { $$ = $1; }
  ;

declarator_list
  : declarator
  | declarator_list ',' declarator
  ;

storage_class_specifier
  : TYPEDEF
  | EXTERN
  | STATIC
  | THREAD_LOCAL
  | AUTO
  | REGISTER
  ;

type_specifier
  : VOID        { $$ = new VoidDataType(); }
  | CHAR        { $$ = new CharDataType(); }
  // | SHORT
  | INT         { $$ = new IntDataType(); }
  | LONG        { $$ = new LongDataType(); }
  // | FLOAT
  // | DOUBLE
  // | SIGNED
  // | UNSIGNED
  // | BOOL
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
  : type_specifier    { $$ = $1; }
  // | type_specifier specifier_qualifier_list
  // | type_qualifier specifier_qualifier_list
  // | type_qualifier
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
  : pointer direct_declarator   { $$ = $2; $$->add_factory($1); }
  | direct_declarator           { $$ = $1; }
  ;

direct_declarator
  : IDENTIFIER                                            { $$ = new Declarator(*$1); delete($1); }
  | '(' declarator ')'                                    { $$ = $2; }
  | direct_declarator '[' ']'                             { $$ = $1; $$->add_factory(new ArrayFactory()); }
  | direct_declarator '[' assignment_expression ']'       { $$ = $1; $$->add_factory(new ArrayFactory($3)); }
  | direct_declarator '(' ')'                             { $$ = $1; $$->add_factory(new FunctionFactory()); }
  | direct_declarator '(' parameter_list ')'              { $$ = $1; $$->add_factory(new FunctionFactory(*$3)); delete($3); }
  | direct_declarator '(' parameter_list ','ELLIPSIS ')'  { $$ = $1; $$->add_factory(new FunctionFactory(*$3, true)); delete($3); }
  ;

pointer
  // : '*' type_qualifier_list pointer
  // | '*' type_qualifier_list
  : pointer '*'                      { $$ = $1; $1->add_factory(new PointerFactory()); }
  | '*'                              { $$ = new PointerFactory(); }
  ;

type_qualifier_list
  : type_qualifier
  | type_qualifier_list type_qualifier
  ;

parameter_list
  : parameter_declaration                       { $$ = new ParameterList{*$1}; delete($1); }
  | parameter_list ',' parameter_declaration    { $$ = $1; $$->push_back(*$3); delete($3); }
  ;

parameter_declaration
  : declaration_specifiers declarator           { $$ = new Parameter($2->build_declaration($1)); delete($2); }
  | declaration_specifiers abstract_declarator  { $$ = new Parameter($2->build_data_type($1)); delete($2); }
  | declaration_specifiers                      { $$ = new Parameter($1); }
  ;

type_name
  : specifier_qualifier_list abstract_declarator  { $$ = $2->build_data_type($1); delete($2); }
  | specifier_qualifier_list                      { $$ = $1; }
  ;

abstract_declarator
  : pointer                               { $$ = $1; }
  | direct_abstract_declarator            { $$ = $1; }
  | pointer direct_abstract_declarator    { $$ = $1; $1->add_factory($2); }
  ;

direct_abstract_declarator
  : '(' abstract_declarator ')'                                     { $$ = $2; }
  | '[' ']'                                                         { $$ = new ArrayFactory(); }
  | '[' assignment_expression ']'                                   { $$ = new ArrayFactory($2); }
  | direct_abstract_declarator '[' ']'                              { $$ = new ArrayFactory($1); }
  | direct_abstract_declarator '[' assignment_expression ']'        { $$ = new ArrayFactory($1, $3); }
  | '(' ')'                                                         { $$ = new FunctionFactory(); }
  | '(' parameter_list ')'                                          { $$ = new FunctionFactory(*$2); delete($2); }
  | '(' parameter_list ',' ELLIPSIS ')'                             { $$ = new FunctionFactory(*$2, true); delete($2); }
  | direct_abstract_declarator '(' ')'                              { $$ = new FunctionFactory($1); }
  | direct_abstract_declarator '(' parameter_list ')'               { $$ = new FunctionFactory($1, *$3); delete($3); }
  | direct_abstract_declarator '(' parameter_list ',' ELLIPSIS ')'  { $$ = new FunctionFactory($1, *$3, true); delete($3); }
  ;

initializer
  // : '{' initializer_list '}'
  // | '{' initializer_list ',' '}'
  : assignment_expression   { $$ = $1; }
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

statement
  : labeled_statement     { $$ = $1; }
  | compound_statement    { $$ = $1; }
  | expression_statement  { $$ = ExpressionStatement::build_statement($1); }
  | selection_statement   { $$ = $1; }
  | iteration_statement   { $$ = $1; }
  | jump_statement        { $$ = $1; }
  ;

labeled_statement
  : IDENTIFIER ':' statement                    { $$ = new LabelStatement(*$1, $3); delete($1); }
  // | CASE constant_expression ':' statement
  // | DEFAULT ':' statement
  ;

compound_statement
  : '{' '}'                   { $$ = new CompoundStatement(); }
  | '{'  block_item_list '}'  { $$ = new CompoundStatement(*$2); delete($2); }
  ;

block_item_list
  : block_item                  { $$ = new StatementList(); $$->insert($$->end(), $1->begin(), $1->end()); delete($1); }
  | block_item_list block_item  { $$ = $1; $$->insert($$->end(), $2->begin(), $2->end()); delete($2); }
  ;

block_item
  : statement     { $$ = new StatementList{$1}; }
  | declaration   {
    $$ = new StatementList();
    for (auto decl : *$1) {
      $$->push_back(new DeclarationStatement(decl));
    }
    delete($1);
  }
  ;

expression_statement
  : ';'               { $$ = nullptr; }
  | expression ';'    { $$ = $1; }
  ;

selection_statement
  : IF '(' expression ')' statement ELSE statement  { $$ = new IfStatement($3, $5, $7); }
  | IF '(' expression ')' statement                 { $$ = new IfStatement($3, $5); }
  // | SWITCH '(' expression ')' statement
  ;

iteration_statement
  : WHILE '(' expression ')' statement                                            { $$ = new WhileStatement($3, $5); }
  | DO statement WHILE '(' expression ')' ';'                                     { $$ = new DoWhileStatement($2, $5); }
  | FOR '(' expression_statement expression_statement ')' statement               { $$ = new ForStatement($3, $4, nullptr, $6); }
  | FOR '(' expression_statement expression_statement expression ')' statement    { $$ = new ForStatement($3, $4, $5, $7); }
  | FOR '(' declaration expression_statement ')' statement                        { $$ = new ForStatement(*$3, $4, nullptr, $6); delete($3); }
  | FOR '(' declaration expression_statement expression ')' statement             { $$ = new ForStatement(*$3, $4, $5, $7); delete($3); }
  ;

jump_statement
  : GOTO IDENTIFIER ';'     { $$ = new GotoStatement(*$2); delete($2); }
  | CONTINUE ';'            { $$ = new ContinueStatement(); }
  | BREAK ';'               { $$ = new BreakStatement(); }
  | RETURN ';'              { $$ = new ReturnStatement(); }
  | RETURN expression ';'   { $$ = new ReturnStatement($2); }
  ;

translation_unit
  : function_definition_list  { functions = *$1; delete($1); }
  ;

/* Implement global variables later */
// external_declaration
//   : function_definition
//   | declaration
//   ;

function_definition_list
  : function_definition                           { $$ = new FunctionDefinitionList{$1}; }
  | function_definition_list function_definition  { $$ = $1; $$->push_back($2); }
  ;

function_definition
  : declaration_specifiers declarator compound_statement  { $$ = new FunctionDefinition($2->build_declaration($1), $3); }
  ;

/* We aren't supporting the K&R syntax */

%%


static void ccerror(YYLTYPE* yyllocp, yyscan_t unused, FunctionDefinitionList& functions, const char *msg) {
  fprintf(stderr, "%s! [Line %d:%d]\n",
    msg,yyllocp->first_line, yyllocp->first_column);
}
