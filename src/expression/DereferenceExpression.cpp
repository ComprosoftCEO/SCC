#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
DereferenceExpression::DereferenceExpression(Expression* expr): UnaryExpression(expr) {}

//
// Clone
//
Expression* DereferenceExpression::clone() const {
  return new DereferenceExpression(this->expr->clone());
}

//
// Visit
//
void DereferenceExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}