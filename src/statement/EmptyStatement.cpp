#include <Statement.h>
#include <Visitor.h>

//
// Visit
//
void EmptyStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
EmptyStatement* EmptyStatement::clone() const {
  return new EmptyStatement();
}
