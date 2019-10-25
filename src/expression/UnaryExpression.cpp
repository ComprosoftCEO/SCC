#include <ConstantExpression.h>
#include <UnaryExpression.h>

//
// Constructor
//
UnaryExpression::UnaryExpression(Expression* expr): expr(expr) {}

//
// Evaluate
//
ConstantValue UnaryExpression::evaluate() {
  // Might throw an exception
  return this->unary_operator(this->expr->evaluate());
}