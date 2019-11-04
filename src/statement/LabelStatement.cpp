#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
LabelStatement::LabelStatement(const std::string& name): name(name) {}

//
// Getters
//
const std::string& LabelStatement::get_name() const {
  return this->name;
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
  return new LabelStatement(this->name);
}
