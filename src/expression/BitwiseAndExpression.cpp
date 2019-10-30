#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
BitwiseAndExpression::BitwiseAndExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
BitwiseAndExpression* BitwiseAndExpression::clone() const {
  return new BitwiseAndExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void BitwiseAndExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}