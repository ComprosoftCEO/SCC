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

//
// Constructor
//
PrintStatement::PrintStatement(): tabs(1) {}

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
  print_tabs(this->tabs);
  printf("{\n");
  this->tabs += 1;

  auto list = stmt.get_statement_list();
  for (auto stmt: list) { Statement::visit(stmt, *this); }

  this->tabs -= 1;
  print_tabs(this->tabs);
  printf("}\n");
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
// Print an if statement
//
void PrintStatement::accept(IfStatement& stmt) {
  print_tabs(this->tabs);
  printf("if (");
  Expression::visit(stmt.get_expression(), PRINT_EXPRESSION);
  printf(")\n");

  this->tabs += 1;
  Statement::visit(stmt.get_then_statement(), *this);
  this->tabs -= 1;

  print_tabs(this->tabs);

  if (stmt.has_else_statement()) {
    printf("else");
    this->tabs += 1;
    Statement::visit(stmt.get_else_statement(), *this);
    this->tabs -= 1;
    print_tabs(this->tabs);
  }

  printf("\n");
}

//
// Print a switch statement
//
void PrintStatement::accept(SwitchStatement& stmt) {
  print_tabs(this->tabs);
  printf("switch(");
  Expression::visit(stmt.get_expression(), PRINT_EXPRESSION);
  printf(")\n");

  this->tabs += 1;
  Statement::visit(stmt.get_statement(), *this);
  this->tabs -= 1;
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
  print_tabs(this->tabs);
  printf("while(");
  Expression::visit(stmt.get_expression(), PRINT_EXPRESSION);
  printf(")\n");

  this->tabs += 1;
  Statement::visit(stmt.get_statement(), *this);
  this->tabs -= 1;
}

//
// Print a do-while loop
//
void PrintStatement::accept(DoWhileStatement& stmt) {
  print_tabs(this->tabs);
  printf("do\n");

  this->tabs += 1;
  Statement::visit(stmt.get_statement(), *this);
  this->tabs -= 1;

  print_tabs(this->tabs);
  printf("while(");
  Expression::visit(stmt.get_expression(), PRINT_EXPRESSION);
  printf(");\n");
}

//
// Print a for-loop
//
void PrintStatement::accept(ForStatement& stmt) {

  print_tabs(this->tabs);
  printf("for (\n");

  Statement* init  = stmt.get_init_statement();
  Expression* cond = stmt.get_cond_expression();
  Expression* loop = stmt.get_loop_expression();

  print_tabs(this->tabs + 1);
  if (init == nullptr) { printf(";\n"); }
  Statement::visit(init, *this);

  print_tabs(this->tabs + 1);
  if (cond == nullptr) { printf(";\n"); }
  Expression::visit(cond, PRINT_EXPRESSION);

  print_tabs(this->tabs + 1);
  Expression::visit(loop, PRINT_EXPRESSION);
  if (loop != nullptr) { printf("\n"); }

  print_tabs(this->tabs);
  printf(")");

  this->tabs += 1;
  Statement::visit(stmt.get_statement(), *this);
  this->tabs -= 1;
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
