#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
AddressOfExpression::AddressOfExpression(Expression* expr): UnaryExpression(expr) {}

//
// Clone
//
AddressOfExpression* AddressOfExpression::clone() const {
  return new AddressOfExpression(this->expr->clone());
}

//
// Visit
//
void AddressOfExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}