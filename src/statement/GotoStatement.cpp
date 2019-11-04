#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
GotoStatement::GotoStatement(const std::string& label): label(label) {}

//
// Getters
//
const std::string& GotoStatement::get_label() const {
  return this->label;
}

//
// Visit
//
void GotoStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
GotoStatement* GotoStatement::clone() const {
  return new GotoStatement(this->label);
}
