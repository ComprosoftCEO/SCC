#include <Expression.h>
#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
ReturnStatement::ReturnStatement(): ReturnStatement(nullptr) {}

ReturnStatement::ReturnStatement(Expression* expr): expr(expr) {}

//
// Destructor
//
ReturnStatement::~ReturnStatement() {
  delete (this->expr);
}

//
// Getters
//
bool ReturnStatement::returns_value() const {
  return this->expr != nullptr;
}

Expression* ReturnStatement::get_return_expression() const {
  return this->expr;
}

//
// Visit
//
void ReturnStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
ReturnStatement* ReturnStatement::clone() const {
  Expression* new_expr = this->expr != nullptr ? this->expr->clone() : nullptr;
  return new ReturnStatement(new_expr);
}
