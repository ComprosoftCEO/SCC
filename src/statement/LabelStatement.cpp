#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
LabelStatement::LabelStatement(const std::string& name, Statement* stmt): name(name), stmt(stmt) {}

//
// Destructor
//
LabelStatement::~LabelStatement() {
  delete (this->stmt);
}

//
// Getters
//
const std::string& LabelStatement::get_name() const {
  return this->name;
}

Statement* LabelStatement::get_statement() const {
  return this->stmt;
}

//
// Visit
//
void LabelStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
LabelStatement* LabelStatement::clone() const {
  return new LabelStatement(this->name, Statement::clone(this->stmt));
}
