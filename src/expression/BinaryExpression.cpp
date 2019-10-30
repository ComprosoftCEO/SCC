#include <Expression.h>

//
// Constructor
//
BinaryExpression::BinaryExpression(Expression* left, Expression* right): left(left), right(right) {}

//
// Destructor
//
BinaryExpression::~BinaryExpression() {
  delete (this->left);
  delete (this->right);
}

//
// Getters
//
Expression* BinaryExpression::get_left_expression() const {
  return this->left;
}

Expression* BinaryExpression::get_right_expression() const {
  return this->right;
}

//
// Evaluate
//
// ConstantValue BinaryExpression::evaluate() {
//   ConstantValue one = this->left->evaluate();
//   ConstantValue two = this->right->evaluate();
//   return this->binary_operator(one, two);
// }
