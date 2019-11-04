#include <Expression.h>
#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
WhileStatement::WhileStatement(Expression* expr, Statement* stmt): expr(expr), stmt(stmt) {}

//
// Destructor
//
WhileStatement::~WhileStatement() {
  delete (this->expr);
  delete (this->stmt);
}

//
// Getters
//
Expression* WhileStatement::get_expression() const {
  return this->expr;
}

Statement* WhileStatement::get_statement() const {
  return this->stmt;
}

//
// Visit
//
void WhileStatement::visit(StatementVisitor& visitor) {
  return visitor.accept(*this);
}

//
// Clone
//
WhileStatement* WhileStatement::clone() const {
  Expression* new_expr = this->expr != nullptr ? this->expr->clone() : nullptr;
  Statement* new_stmt  = this->stmt != nullptr ? this->stmt->clone() : nullptr;
  return new WhileStatement(new_expr, new_stmt);
}
