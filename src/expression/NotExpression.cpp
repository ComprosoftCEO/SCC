#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
NotExpression::NotExpression(Expression* expr): UnaryExpression(expr) {}

//
// Clone
//
Expression* NotExpression::clone() const {
  return new NotExpression(this->expr->clone());
}

//
// Visit
//
void NotExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}