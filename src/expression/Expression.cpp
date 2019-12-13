#include <Expression.h>
#include <Visitor.h>

//
// Default evaluate method
//
ConstantExpression* Expression::evaluate() const {
  return nullptr;
}

//
// Static visit method
//
void Expression::visit(Expression* expr, ExpressionVisitor& visitor) {
  if (expr != nullptr) { expr->visit(visitor); }
}

//
// Static clone method
//
Expression* Expression::clone(Expression* expr) {
  return (expr != nullptr) ? expr->clone() : nullptr;
}

//
// Static evaluate method
//
ConstantExpression* Expression::evaluate(Expression* expr) {
  return (expr != nullptr) ? expr->evaluate() : nullptr;
}
