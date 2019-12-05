#include <DataType.h>
#include <Declaration.h>
#include <Expression.h>
#include <PrintVisitor.h>
#include <Statement.h>
#include <cstdio>

// Global stateless printers
static PrintDataType PRINT_DATA_TYPE;
static PrintExpression PRINT_EXPRESSION;

// Print a list of tabs
static inline void print_tabs(int tabs) {
  for (int i = 0; i < tabs; ++i) { printf("  "); }
}

// Test if a statement is compound (for bracket formatting)
static inline bool is_compound_statement(Statement* stmt) {
  return dynamic_cast<CompoundStatement*>(stmt) != nullptr;
}

//
// Constructor
//
PrintStatement::PrintStatement(): tabs(1), ignore_brackets(false) {}

//
// Statement with no code
//
void PrintStatement::accept(EmptyStatement& stmt) {
  print_tabs(this->tabs);
  printf(";\n");
}

//
// Statement that stores a single declaration
//
void PrintStatement::accept(DeclarationStatement& stmt) {

  Declaration* decl = stmt.get_declaration();
  if (decl == nullptr) { return; }

  print_tabs(this->tabs);
  decl->print();
  printf(";\n");
}

//
// Print a label
//
void PrintStatement::accept(LabelStatement& stmt) {
  print_tabs(this->tabs - 1);
  printf("%s:\n", stmt.get_name().c_str());
  Statement::visit(stmt.get_statement(), *this);
}

//
// Print a case label
//
void PrintStatement::accept(CaseStatement& stmt) {
  print_tabs(this->tabs - 1);
  printf("case ");
  Expression::visit(stmt.get_value(), PRINT_EXPRESSION);
  printf(":\n");
  Statement::visit(stmt.get_statement(), *this);
}

//
// Print a default case label
//
void PrintStatement::accept(DefaultCaseStatement& stmt) {
  print_tabs(this->tabs - 1);
  printf("default:\n");
  Statement::visit(stmt.get_statement(), *this);
}

//
// Print a block statement
//
void PrintStatement::accept(CompoundStatement& stmt) {

  const bool ignore_brackets = this->ignore_brackets;
  this->ignore_brackets      = false;

  if (!ignore_brackets) {
    print_tabs(this->tabs);
    printf("{\n");
    this->tabs += 1;
  }

  auto list = stmt.get_statement_list();
  for (auto stmt: list) { Statement::visit(stmt, *this); }

  if (!ignore_brackets) {
    this->tabs -= 1;
    print_tabs(this->tabs);
    printf("}\n");
  }
}

//
// Print an expression
//
void PrintStatement::accept(ExpressionStatement& stmt) {
  print_tabs(this->tabs);
  Expression::visit(stmt.get_expression(), PRINT_EXPRESSION);
  printf(";\n");
}

//
// Print an if statement (ugly then-else logic)
//
void PrintStatement::accept(IfStatement& stmt) {

  Statement* then_stmt     = stmt.get_then_statement();
  Statement* else_stmt     = stmt.get_else_statement();
  const bool then_compound = is_compound_statement(then_stmt);
  const bool else_compound = is_compound_statement(else_stmt);

  // If expression
  print_tabs(this->tabs);
  printf("if (");
  Expression::visit(stmt.get_expression(), PRINT_EXPRESSION);
  printf(") %c\n", then_compound ? '{' : '\0');

  // Then statement
  this->tabs += 1;
  this->visitIgnoreBrackets(stmt.get_then_statement());
  this->tabs -= 1;

  if (then_compound) {
    print_tabs(this->tabs);
    printf("} ");
  }

  // Else statement
  if (stmt.has_else_statement()) {
    if (!then_compound) { print_tabs(this->tabs); }
    printf("else %c\n", else_compound ? '{' : '\0');

    this->tabs += 1;
    this->visitIgnoreBrackets(stmt.get_else_statement());
    this->tabs -= 1;

    print_tabs(this->tabs);
    printf("%c", else_compound ? '}' : '\0');
  }

  printf("\n");
}

//
// Print a switch statement
//
void PrintStatement::accept(SwitchStatement& stmt) {

  Statement* s           = stmt.get_statement();
  const bool is_compound = is_compound_statement(s);

  // Switch expression
  print_tabs(this->tabs);
  printf("switch(");
  Expression::visit(stmt.get_expression(), PRINT_EXPRESSION);
  printf(") %c\n", is_compound ? '{' : '\0');

  // Indent by 2 so that case labels are indented by 1
  this->tabs += 2;
  this->visitIgnoreBrackets(s);
  this->tabs -= 2;

  if (is_compound) {
    print_tabs(this->tabs);
    printf("}\n");
  }
}

//
// Print a goto statement
//
void PrintStatement::accept(GotoStatement& stmt) {
  print_tabs(this->tabs);
  printf("goto %s;\n", stmt.get_label().c_str());
}

//
// Print a while loop
//
void PrintStatement::accept(WhileStatement& stmt) {

  Statement* s           = stmt.get_statement();
  const bool is_compound = is_compound_statement(s);

  // While expression
  print_tabs(this->tabs);
  printf("while(");
  Expression::visit(stmt.get_expression(), PRINT_EXPRESSION);
  printf(") %c\n", is_compound ? '{' : '\0');

  // Statement
  this->tabs += 1;
  this->visitIgnoreBrackets(s);
  this->tabs -= 1;

  if (is_compound) {
    print_tabs(this->tabs);
    printf("}\n");
  }
}

//
// Print a do-while loop
//
void PrintStatement::accept(DoWhileStatement& stmt) {
  Statement* s           = stmt.get_statement();
  const bool is_compound = is_compound_statement(s);

  // Do header
  print_tabs(this->tabs);
  printf("do %c\n", is_compound ? '{' : '\0');

  // Statement
  this->tabs += 1;
  this->visitIgnoreBrackets(s);
  this->tabs -= 1;

  // While expression
  print_tabs(this->tabs);
  printf("%c while(", is_compound ? '}' : '\0');
  Expression::visit(stmt.get_expression(), PRINT_EXPRESSION);
  printf(");\n");
}

//
// Print a for-loop (ugly complicated logic)
//
void PrintStatement::accept(ForStatement& stmt) {

  Statement* s           = stmt.get_statement();
  const bool is_compound = is_compound_statement(s);

  Statement* init  = stmt.get_init_statement();
  Expression* cond = stmt.get_cond_expression();
  Expression* loop = stmt.get_loop_expression();

  // For keyword
  print_tabs(this->tabs);
  printf("for (\n");

  // Init statement (might be compound)
  this->tabs += 1;
  if (init == nullptr) {
    print_tabs(this->tabs);
    printf(";\n");
  }
  Statement::visit(init, *this);
  this->tabs -= 1;

  // Condition expression
  print_tabs(this->tabs + 1);
  Expression::visit(cond, PRINT_EXPRESSION);
  printf(";\n");

  // Loop expression
  if (loop != nullptr) {
    print_tabs(this->tabs + 1);
    Expression::visit(loop, PRINT_EXPRESSION);
    printf("\n");
  }

  print_tabs(this->tabs);
  printf(") %c\n", is_compound ? '{' : '\0');

  // Statement
  this->tabs += 1;
  this->visitIgnoreBrackets(s);
  this->tabs -= 1;

  if (is_compound) {
    print_tabs(this->tabs);
    printf("}\n");
  }
}

//
// "continue" keyword
//
void PrintStatement::accept(ContinueStatement& stmt) {
  print_tabs(this->tabs);
  printf("continue;\n");
}

//
// "break" keyword
//
void PrintStatement::accept(BreakStatement& stmt) {
  print_tabs(this->tabs);
  printf("break;\n");
}

//
// "return" keyword
//
void PrintStatement::accept(ReturnStatement& stmt) {
  print_tabs(this->tabs);
  printf("return");

  if (stmt.returns_value()) {
    printf(" ");
    Expression::visit(stmt.get_return_expression(), PRINT_EXPRESSION);
  }

  printf(";\n");
}

//
// Special case for bracket formatting
//
void PrintStatement::visitIgnoreBrackets(Statement* stmt) {
  this->ignore_brackets = true;
  Statement::visit(stmt, *this);
  this->ignore_brackets = false;
}
