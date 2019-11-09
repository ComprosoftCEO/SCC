#include <Expression.h>
#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
IfStatement::IfStatement(Expression* expr, Statement* then_stmt):
  IfStatement(expr, then_stmt, nullptr) {}

IfStatement::IfStatement(Expression* expr, Statement* then_stmt, Statement* else_stmt):
  expr(expr), then_stmt(then_stmt), else_stmt(else_stmt) {}

//
// Destructor
//
IfStatement::~IfStatement() {
  delete (this->expr);
  delete (this->then_stmt);
  delete (this->else_stmt);
}

//
// Getters
//
Expression* IfStatement::get_expression() const {
  return this->expr;
}

Statement* IfStatement::get_then_statement() const {
  return this->then_stmt;
}

bool IfStatement::has_else_statement() const {
  return this->else_stmt != nullptr;
}

Statement* IfStatement::get_else_statement() const {
  return this->else_stmt;
}

//
// Visit
//
void IfStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
IfStatement* IfStatement::clone() const {
  Expression* new_expr = Expression::clone(this->expr);
  Statement* new_then  = Statement::clone(this->then_stmt);
  Statement* new_else  = Statement::clone(this->else_stmt);
  return new IfStatement(new_expr, new_then, new_else);
}
