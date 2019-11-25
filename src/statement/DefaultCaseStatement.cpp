#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
DefaultCaseStatement::DefaultCaseStatement(Statement* stmt): stmt(stmt) {}

//
// Destructor
//
DefaultCaseStatement::~DefaultCaseStatement() {
  delete (this->stmt);
}

//
// Getters
//
Statement* DefaultCaseStatement::get_statement() const {
  return this->stmt;
}

//
// Visit
//
void DefaultCaseStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
DefaultCaseStatement* DefaultCaseStatement::clone() const {
  return new DefaultCaseStatement(Statement::clone(this->stmt));
}
