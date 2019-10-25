#include <BinaryExpression.h>

//
// Constructor
//
BinaryExpression::BinaryExpression(Expression* left, Expression* right): left(left), right(right) {}

//
// Evaluate
//
ConstantValue BinaryExpression::evaluate() {
  ConstantValue one = this->left->evaluate();
  ConstantValue two = this->right->evaluate();
  return this->binary_operator(one, two);
}
