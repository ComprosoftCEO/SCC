#include <Expression.h>
#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
CaseStatement::CaseStatement(Expression* value, Statement* stmt): value(value), stmt(stmt) {}

//
// Destructor
//
CaseStatement::~CaseStatement() {
  delete (this->value);
  delete (this->stmt);
}

//
// Getters
//
Expression* CaseStatement::get_value() const {
  return this->value;
}

Statement* CaseStatement::get_statement() const {
  return this->stmt;
}

//
// Visit
//
void CaseStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
CaseStatement* CaseStatement::clone() const {
  return new CaseStatement(Expression::clone(this->value), Statement::clone(this->stmt));
}
