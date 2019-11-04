#include <Statement.h>
#include <Visitor.h>

//
// Visit
//
void ContinueStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
ContinueStatement* ContinueStatement::clone() const {
  return new ContinueStatement();
}
