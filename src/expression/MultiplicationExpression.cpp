#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
MultiplicationExpression::MultiplicationExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
Expression* MultiplicationExpression::clone() const {
  return new MultiplicationExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void MultiplicationExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}