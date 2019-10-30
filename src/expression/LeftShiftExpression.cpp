#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
LeftShiftExpression::LeftShiftExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
Expression* LeftShiftExpression::clone() const {
  return new LeftShiftExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void LeftShiftExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}