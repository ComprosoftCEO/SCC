#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
RightShiftExpression::RightShiftExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
Expression* RightShiftExpression::clone() const {
  return new RightShiftExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void RightShiftExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}