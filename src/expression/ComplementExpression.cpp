#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
ComplementExpression::ComplementExpression(Expression* expr): UnaryExpression(expr) {}

//
// Clone
//
ComplementExpression* ComplementExpression::clone() const {
  return new ComplementExpression(this->expr->clone());
}

//
// Visit
//
void ComplementExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}
