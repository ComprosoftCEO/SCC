#include <Statement.h>
#include <Visitor.h>

//
// Static visit method
//
void Statement::visit(Statement* stmt, StatementVisitor& visitor) {
  if (stmt != nullptr) { stmt->visit(visitor); }
}

//
// Static clone method
//
Statement* Statement::clone(Statement* stmt) {
  return stmt != nullptr ? stmt->clone() : nullptr;
}
