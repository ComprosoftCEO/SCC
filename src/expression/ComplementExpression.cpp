#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
ComplementExpression::ComplementExpression(Expression* expr): UnaryExpression(expr) {}

//
// Clone
//
Expression* ComplementExpression::clone() const {
  return new ComplementExpression(this->expr->clone());
}

//
// Visit
//
void ComplementExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}
