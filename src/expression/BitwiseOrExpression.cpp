#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
BitwiseOrExpression::BitwiseOrExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
BitwiseOrExpression* BitwiseOrExpression::clone() const {
  return new BitwiseOrExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void BitwiseOrExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}