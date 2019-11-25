#include <Expression.h>
#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
SwitchStatement::SwitchStatement(Expression* expr, Statement* stmt): expr(expr), stmt(stmt) {}

//
// Destructor
//
SwitchStatement::~SwitchStatement() {
  delete (this->expr);
  delete (this->stmt);
}

//
// Getters
//
Expression* SwitchStatement::get_expression() const {
  return this->expr;
}

Statement* SwitchStatement::get_statement() const {
  return this->stmt;
}

//
// Visit
//
void SwitchStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
SwitchStatement* SwitchStatement::clone() const {
  return new SwitchStatement(Expression::clone(this->expr), Statement::clone(this->stmt));
}
