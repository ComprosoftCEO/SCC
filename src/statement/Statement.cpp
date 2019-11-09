#include <Statement.h>
#include <Visitor.h>

//
// Static clone method
//
Statement* Statement::clone(Statement* stmt) {
  return stmt != nullptr ? stmt->clone() : nullptr;
}
