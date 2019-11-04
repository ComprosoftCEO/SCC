#include <Expression.h>
#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
DoWhileStatement::DoWhileStatement(Statement* stmt, Expression* expr): stmt(stmt), expr(expr) {}

//
// Destructor
//
DoWhileStatement::~DoWhileStatement() {
  delete (this->expr);
  delete (this->stmt);
}

//
// Getters
//
Expression* DoWhileStatement::get_expression() const {
  return this->expr;
}

Statement* DoWhileStatement::get_statement() const {
  return this->stmt;
}

//
// Visit
//
void DoWhileStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
DoWhileStatement* DoWhileStatement::clone() const {
  Expression* new_expr = this->expr != nullptr ? this->expr->clone() : nullptr;
  Statement* new_stmt  = this->stmt != nullptr ? this->stmt->clone() : nullptr;
  return new DoWhileStatement(new_stmt, new_expr);
}
