/* Lexer for C tokens */

/* Basic Types */
OCT       [0-7]
DIG       [0-9]
NZ_DIG    [1-9]
LTR       [a-zA-Z_]
ALNUM     [a-zA-Z_0-9]
HEX       [a-fA-F0-9]
EXP       ([Ee][+-]?{DIG}+)
HXP       ([Pp][+-]?{DIG}+)
FLT_SFX   (f|F|l|L)
CNST_PFX  (u|U|L)
STR_PFX   (u8|u|U|L)
EXP_SFX   (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WHTSP     [ \t\v\n\f]

/* Integer Types */
DEC_INT   ([-]?{NZ_DIG}{DIG}*|[0])
HEX_INT   {HEX}+
OCT_INT   {OCT}+

/* Integer Prefixes */
HEX_PFX   (0[xX])
OCT_PFX   0

/* Integer Suffixes */
U_SFX     (u|U)
L_SFX     (l|L)
UL_SFX    ([uU][lL]|[lL][uU])
LL_SFX    (ll|LL)
ULL_SFX   ([uU](ll|LL)|(ll|LL)[uU])

%{
  #include <DataType.h>
  #include <DataTypeFactory.h>
  #include <Declarator.h>
  #include <Expression.h>
  #include <string>
  #include "c.tab.h"

  //Track line numbers for parsed tokens
  #define YY_USER_ACTION                                           \
  yylloc->first_line = yylloc->last_line;                          \
  yylloc->first_column = yylloc->last_column;                      \
  if (yylloc->last_line == yylineno) {                             \
    yylloc->last_column += yyleng;                                 \
  } else {                                                         \
    yylloc->last_line = yylineno;                                  \
    yylloc->last_column = yytext + yyleng - strrchr(yytext, '\n'); \
  }

  extern int sym_type(const char *);    /* returns type from symbol table */
  #define sym_type(identifier) IDENTIFIER /* with no symbol table, fake it */

  static int check_type(void);      /* Solves C typedef problem */
%}

%x COMMENT

%option yylineno noyywrap 8bit nodefault                        
%option reentrant bison-bridge bison-locations 
%option prefix="cc"
%%

"/*"              { BEGIN(COMMENT); }
<COMMENT>"*/"     { BEGIN(INITIAL); }
"//".*            { /* Consume Comment */ }

"auto"            { return(AUTO); }
"break"           { return(BREAK); }
"case"            { return(CASE); }
"char"            { return(CHAR); }
"const"           { return(CONST); }
"continue"        { return(CONTINUE); }
"default"         { return(DEFAULT); }
"do"              { return(DO); }
"double"          { return(DOUBLE); }
"else"            { return(ELSE); }
"enum"            { return(ENUM); }
"extern"          { return(EXTERN); }
"float"           { return(FLOAT); }
"for"             { return(FOR); }
"goto"            { return(GOTO); }
"if"              { return(IF); }
"inline"          { return(INLINE); }
"int"             { return(INT); }
"long"            { return(LONG); }
"register"        { return(REGISTER); }
"restrict"        { return(RESTRICT); }
"return"          { return(RETURN); }
"short"           { return(SHORT); }
"signed"          { return(SIGNED); }
"sizeof"          { return(SIZEOF); }
"static"          { return(STATIC); }
"struct"          { return(STRUCT); }
"switch"          { return(SWITCH); }
"typedef"         { return(TYPEDEF); }
"union"           { return(UNION); }
"unsigned"        { return(UNSIGNED); }
"void"            { return(VOID); }
"volatile"        { return(VOLATILE); }
"while"           { return(WHILE); }

"_Alignas"        { return(ALIGNAS); }
"_Alignof"        { return(ALIGNOF); }
"_Atomic"         { return(ATOMIC); }
"_Bool"           { return(BOOL); }
"_Complex"        { return(COMPLEX); }
"_Generic"        { return(GENERIC); }
"_Imaginary"      { return(IMAGINARY); }
"_Noreturn"       { return(NORETURN); }
"_Static_assert"  { return(STATIC_ASSERT); }
"_Thread_local"   { return(THREAD_LOCAL); }
"__func__"        { return(FUNC_NAME); }

{LTR}{ALNUM}*     { return check_type(); }

 /* Integers */
{DEC_INT}               { yylval->ival   = std::stoi(yytext);   return INT_CONSTANT; }
{DEC_INT}{U_SFX}        { yylval->uival  = std::stoul(yytext);  return UINT_CONSTANT; }
{DEC_INT}{L_SFX}        { yylval->lval   = std::stol(yytext);   return LONG_CONSTANT; }
{DEC_INT}{UL_SFX}       { yylval->ulval  = std::stoul(yytext);  return ULONG_CONSTANT; }
{DEC_INT}{LL_SFX}       { yylval->llval  = std::stoll(yytext);  return LONGLONG_CONSTANT; }
{DEC_INT}{ULL_SFX}      { yylval->ullval = std::stoull(yytext); return ULONGLONG_CONSTANT; }

 /* Hex Integers */
{HEX_PFX}{HEX_INT}               { yylval->ival   = std::stoi(yytext, 0, 16);   return INT_CONSTANT; }
{HEX_PFX}{HEX_INT}{U_SFX}        { yylval->uival  = std::stoul(yytext, 0, 16);  return UINT_CONSTANT; }
{HEX_PFX}{HEX_INT}{L_SFX}        { yylval->lval   = std::stol(yytext, 0, 16);   return LONG_CONSTANT; }
{HEX_PFX}{HEX_INT}{UL_SFX}       { yylval->ulval  = std::stoul(yytext, 0, 16);  return ULONG_CONSTANT; }
{HEX_PFX}{HEX_INT}{LL_SFX}       { yylval->llval  = std::stoll(yytext, 0, 16);  return LONGLONG_CONSTANT; }
{HEX_PFX}{HEX_INT}{ULL_SFX}      { yylval->ullval = std::stoull(yytext, 0, 16); return ULONGLONG_CONSTANT; }

 /* Octal Integers */
{OCT_PFX}{OCT_INT}               { yylval->ival   = std::stoi(yytext, 0, 16);   return INT_CONSTANT; }
{OCT_PFX}{OCT_INT}{U_SFX}        { yylval->uival  = std::stoul(yytext, 0, 16);  return UINT_CONSTANT; }
{OCT_PFX}{OCT_INT}{L_SFX}        { yylval->lval   = std::stol(yytext, 0, 16);   return LONG_CONSTANT; }
{OCT_PFX}{OCT_INT}{UL_SFX}       { yylval->ulval  = std::stoul(yytext, 0, 16);  return ULONG_CONSTANT; }
{OCT_PFX}{OCT_INT}{LL_SFX}       { yylval->llval  = std::stoll(yytext, 0, 16);  return LONGLONG_CONSTANT; }
{OCT_PFX}{OCT_INT}{ULL_SFX}      { yylval->ullval = std::stoull(yytext, 0, 16); return ULONGLONG_CONSTANT; }


 /* Other integer?? No idea how to parse this!
{CNST_PFX}?"'"([^'\\\n]|{EXP_SFX})+"'"    { return I_CONSTANT; }
 */

 /*
{DIG}+{EXP}{FLT_SFX}?                     { return F_CONSTANT; }
{DIG}*"."{DIG}+{EXP}?{FLT_SFX}?           { return F_CONSTANT; }
{DIG}+"."{EXP}?{FLT_SFX}?                 { return F_CONSTANT; }
{HEX_PFX}{HEX}+{HXP}{FLT_SFX}?            { return F_CONSTANT; }
{HEX_PFX}{HEX}*"."{HEX}+{HXP}{FLT_SFX}?   { return F_CONSTANT; }
{HEX_PFX}{HEX}+"."{HXP}{FLT_SFX}?         { return F_CONSTANT; }
 */

({STR_PFX}?\"([^"\\\n]|{EXP_SFX})*\"{WHTSP}*)+  { return STRING_LITERAL; }

"..."         { return ELLIPSIS; }
">>="         { return RIGHT_ASSIGN; }
"<<="         { return LEFT_ASSIGN; }
"+="          { return ADD_ASSIGN; }
"-="          { return SUB_ASSIGN; }
"*="          { return MUL_ASSIGN; }
"/="          { return DIV_ASSIGN; }
"%="          { return MOD_ASSIGN; }
"&="          { return AND_ASSIGN; }
"^="          { return XOR_ASSIGN; }
"|="          { return OR_ASSIGN; }
">>"          { return RIGHT_OP; }
"<<"          { return LEFT_OP; }
"++"          { return INC_OP; }
"--"          { return DEC_OP; }
"->"          { return PTR_OP; }
"&&"          { return AND_OP; }
"||"          { return OR_OP; }
"<="          { return LE_OP; }
">="          { return GE_OP; }
"=="          { return EQ_OP; }
"!="          { return NE_OP; }
";"           { return ';'; }
("{"|"<%")    { return '{'; }
("}"|"%>")    { return '}'; }
","           { return ','; }
":"           { return ':'; }
"="           { return '='; }
"("           { return '('; }
")"           { return ')'; }
("["|"<:")    { return '['; }
("]"|":>")    { return ']'; }
"."           { return '.'; }
"&"           { return '&'; }
"!"           { return '!'; }
"~"           { return '~'; }
"-"           { return '-'; }
"+"           { return '+'; }
"*"           { return '*'; }
"/"           { return '/'; }
"%"           { return '%'; }
"<"           { return '<'; }
">"           { return '>'; }
"^"           { return '^'; }
"|"           { return '|'; }
"?"           { return '?'; }

{WHTSP}+      { /* Whitespace separates tokens */ }
.             { /* Discard bad characters */ }

%%

static int check_type(void) {
    switch (sym_type(yytext)) {
    case TYPEDEF_NAME:                /* previously defined */
        return TYPEDEF_NAME;
    case ENUMERATION_CONSTANT:        /* previously defined */
        return ENUMERATION_CONSTANT;
    default:                          /* includes undefined */
        return IDENTIFIER;
    }
}
