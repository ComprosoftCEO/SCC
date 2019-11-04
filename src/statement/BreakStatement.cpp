#include <Statement.h>
#include <Visitor.h>

//
// Visit
//
void BreakStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
BreakStatement* BreakStatement::clone() const {
  return new BreakStatement();
}
