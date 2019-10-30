#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
LessThanOrEqualExpression::LessThanOrEqualExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
Expression* LessThanOrEqualExpression::clone() const {
  return new LessThanOrEqualExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void LessThanOrEqualExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}