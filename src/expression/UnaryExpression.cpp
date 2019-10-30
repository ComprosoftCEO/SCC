#include <ConstantExpression.h>
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
/*ConstantValue UnaryExpression::evaluate() {
  // Might throw an exception
  return this->unary_operator(this->expr->evaluate());
}*/