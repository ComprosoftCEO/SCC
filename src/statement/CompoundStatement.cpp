#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
CompoundStatement::CompoundStatement(const StatementList& stmt_list): stmt_list(stmt_list) {}

//
// Destructor
//
CompoundStatement::~CompoundStatement() {
  for (auto stmt: this->stmt_list) { delete (stmt); }
}

//
// Getters
//
const StatementList& CompoundStatement::get_statement_list() const {
  return this->stmt_list;
}

//
// Visit
//
void CompoundStatement::visit(StatementVisitor& visitor) {
  return visitor.accept(*this);
}

//
// Clone
//
CompoundStatement* CompoundStatement::clone() const {
  StatementList new_list;
  for (auto stmt: this->stmt_list) {
    new_list.push_back(stmt != nullptr ? stmt->clone() : nullptr);
  }
  return new CompoundStatement(new_list);
}
