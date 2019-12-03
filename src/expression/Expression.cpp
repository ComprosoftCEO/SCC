#include <Expression.h>
#include <Visitor.h>

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
  return expr != nullptr ? expr->clone() : nullptr;
}
