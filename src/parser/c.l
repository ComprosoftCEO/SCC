/* Lexer for C tokens */

OCT			[0-7]
DIG			[0-9]
NZ_DIG		[1-9]
LTR			[a-zA-Z_]
ALNUM		[a-zA-Z_0-9]
HEX			[a-fA-F0-9]
HEX_PFX		(0[xX])
EXP			([Ee][+-]?{DIG}+)
HXP			([Pp][+-]?{DIG}+)
FLT_SFX		(f|F|l|L)
INT_SFX		((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))
CNST_PFX	(u|U|L)
STR_PFX		(u8|u|U|L)
EXP_SFX		(\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WHTSP 		[ \t\v\n\f]


%{
	//#include "InsanityParser.h"
	#include "c.tab.h"

	//Track line numbers for parsed tokens
	#define YY_USER_ACTION                                             \
	yylloc->first_line = yylloc->last_line;                            \
	yylloc->first_column = yylloc->last_column;                        \
	if (yylloc->last_line == yylineno)                                 \
		yylloc->last_column += yyleng;                                 \
	else {                                                             \
		yylloc->last_line = yylineno;                                  \
		yylloc->last_column = yytext + yyleng - strrchr(yytext, '\n'); \
	}

	extern int sym_type(const char *);  	/* returns type from symbol table */
	#define sym_type(identifier) IDENTIFIER /* with no symbol table, fake it */

	static int check_type(void);			/* Solves C typedef problem */
%}

%x COMMENT

%option yylineno noyywrap 8bit nodefault                        
%option reentrant bison-bridge bison-locations 
%%

"/*"					{ BEGIN(COMMENT); }
<COMMENT>"*/"			{ BEGIN(INITIAL); }
"//".*					{ /* Consume Comment */ }

"auto"					{ return(AUTO); }
"break"					{ return(BREAK); }
"case"					{ return(CASE); }
"char"					{ return(CHAR); }
"const"					{ return(CONST); }
"continue"				{ return(CONTINUE); }
"default"				{ return(DEFAULT); }
"do"					{ return(DO); }
"double"				{ return(DOUBLE); }
"else"					{ return(ELSE); }
"enum"					{ return(ENUM); }
"extern"				{ return(EXTERN); }
"float"					{ return(FLOAT); }
"for"					{ return(FOR); }
"goto"					{ return(GOTO); }
"if"					{ return(IF); }
"inline"				{ return(INLINE); }
"int"					{ return(INT); }
"long"					{ return(LONG); }
"register"				{ return(REGISTER); }
"restrict"				{ return(RESTRICT); }
"return"				{ return(RETURN); }
"short"					{ return(SHORT); }
"signed"				{ return(SIGNED); }
"sizeof"				{ return(SIZEOF); }
"static"				{ return(STATIC); }
"struct"				{ return(STRUCT); }
"switch"				{ return(SWITCH); }
"typedef"				{ return(TYPEDEF); }
"union"					{ return(UNION); }
"unsigned"				{ return(UNSIGNED); }
"void"					{ return(VOID); }
"volatile"				{ return(VOLATILE); }
"while"					{ return(WHILE); }

"_Alignas"				{ return(ALIGNAS); }
"_Alignof"				{ return(ALIGNOF); }
"_Atomic"				{ return(ATOMIC); }
"_Bool"					{ return(BOOL); }
"_Complex"				{ return(COMPLEX); }
"_Generic"				{ return(GENERIC); }
"_Imaginary"			{ return(IMAGINARY); }
"_Noreturn"				{ return(NORETURN); }
"_Static_assert"		{ return(STATIC_ASSERT); }
"_Thread_local"			{ return(THREAD_LOCAL); }
"__func__"				{ return(FUNC_NAME); }

{LTR}{ALNUM}*			{ return check_type(); }

{HEX_PFX}{HEX}+{INT_SFX}?				{ return I_CONSTANT; }
{NZ_DIG}{DIG}*{INT_SFX}?				{ return I_CONSTANT; }
"0"{OCT}*{INT_SFX}?						{ return I_CONSTANT; }
{CNST_PFX}?"'"([^'\\\n]|{EXP_SFX})+"'"	{ return I_CONSTANT; }

{DIG}+{EXP}{FLT_SFX}?						{ return F_CONSTANT; }
{DIG}*"."{DIG}+{EXP}?{FLT_SFX}?				{ return F_CONSTANT; }
{DIG}+"."{EXP}?{FLT_SFX}?					{ return F_CONSTANT; }
{HEX_PFX}{HEX}+{HXP}{FLT_SFX}?				{ return F_CONSTANT; }
{HEX_PFX}{HEX}*"."{HEX}+{HXP}{FLT_SFX}?		{ return F_CONSTANT; }
{HEX_PFX}{HEX}+"."{HXP}{FLT_SFX}?			{ return F_CONSTANT; }

({STR_PFX}?\"([^"\\\n]|{EXP_SFX})*\"{WHTSP}*)+	{ return STRING_LITERAL; }

"..."					{ return ELLIPSIS; }
">>="					{ return RIGHT_ASSIGN; }
"<<="					{ return LEFT_ASSIGN; }
"+="					{ return ADD_ASSIGN; }
"-="					{ return SUB_ASSIGN; }
"*="					{ return MUL_ASSIGN; }
"/="					{ return DIV_ASSIGN; }
"%="					{ return MOD_ASSIGN; }
"&="					{ return AND_ASSIGN; }
"^="					{ return XOR_ASSIGN; }
"|="					{ return OR_ASSIGN; }
">>"					{ return RIGHT_OP; }
"<<"					{ return LEFT_OP; }
"++"					{ return INC_OP; }
"--"					{ return DEC_OP; }
"->"					{ return PTR_OP; }
"&&"					{ return AND_OP; }
"||"					{ return OR_OP; }
"<="					{ return LE_OP; }
">="					{ return GE_OP; }
"=="					{ return EQ_OP; }
"!="					{ return NE_OP; }
";"						{ return ';'; }
("{"|"<%")				{ return '{'; }
("}"|"%>")				{ return '}'; }
","						{ return ','; }
":"						{ return ':'; }
"="						{ return '='; }
"("						{ return '('; }
")"						{ return ')'; }
("["|"<:")				{ return '['; }
("]"|":>")				{ return ']'; }
"."						{ return '.'; }
"&"						{ return '&'; }
"!"						{ return '!'; }
"~"						{ return '~'; }
"-"						{ return '-'; }
"+"						{ return '+'; }
"*"						{ return '*'; }
"/"						{ return '/'; }
"%"						{ return '%'; }
"<"						{ return '<'; }
">"						{ return '>'; }
"^"						{ return '^'; }
"|"						{ return '|'; }
"?"						{ return '?'; }

{WHTSP}+				{ /* Whitespace separates tokens */ }
.						{ /* Discard bad characters */ }

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
