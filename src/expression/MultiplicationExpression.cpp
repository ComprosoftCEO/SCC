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
MultiplicationExpression* MultiplicationExpression::clone() const {
  return new MultiplicationExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void MultiplicationExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}