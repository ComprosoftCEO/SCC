#include <Expression.h>

//
// Constructor
//
UnaryExpression::UnaryExpression(Expression* expr): expr(expr) {}

//
// Destructor
//
UnaryExpression::~UnaryExpression() {
  delete (this->expr);
}

//
// Getters
//
Expression* UnaryExpression::get_expression() const {
  return this->expr;
}

//
// Evaluate
//
ConstantExpression* UnaryExpression::evaluate() const {
  ConstantExpression* eval = Expression::evaluate(this->expr);

  ConstantExpression* retval = this->get_evaluator().evaluate(eval);
  delete (eval); // Might be NULL

  return retval;
}