#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
MinusExpression::MinusExpression(Expression* expr): UnaryExpression(expr) {}

//
// Clone
//
Expression* MinusExpression::clone() const {
  return new MinusExpression(this->expr->clone());
}

//
// Visit
//
void MinusExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}