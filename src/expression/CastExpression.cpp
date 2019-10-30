#include <DataType.h>
#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
CastExpression::CastExpression(Expression* expr, DataType* cast_to): expr(expr), cast_to(cast_to) {}

//
// Destructor
//
CastExpression::~CastExpression() {
  delete (this->expr);
  delete (this->cast_to);
}

//
// Getters
//
Expression* CastExpression::get_expression() {
  return this->expr;
}

DataType* CastExpression::get_cast_type() {
  return this->cast_to;
}

//
// Clone
//
CastExpression* CastExpression::clone() const {
  // TODO: Implement this method
  return nullptr;
}

//
// Visit
//
void CastExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}