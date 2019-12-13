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
ConstantExpression* BinaryExpression::evaluate() const {
  ConstantExpression* left_eval  = Expression::evaluate(this->left);
  ConstantExpression* right_eval = Expression::evaluate(this->right);

  ConstantExpression* retval = this->get_evaluator().evaluate(left_eval, right_eval);
  delete (left_eval);  // Might be NULL
  delete (right_eval); // Might be NULL

  return retval;
}
