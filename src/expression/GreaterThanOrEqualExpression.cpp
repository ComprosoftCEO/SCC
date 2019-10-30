#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
GreaterThanOrEqualExpression::GreaterThanOrEqualExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
Expression* GreaterThanOrEqualExpression::clone() const {
  return new GreaterThanOrEqualExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void GreaterThanOrEqualExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}