#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
AlignofExpression::AlignofExpression(Expression* expr): UnaryExpression(expr) {}

//
// Clone
//
AlignofExpression* AlignofExpression::clone() const {
  return new AlignofExpression(this->expr->clone());
}

//
// Visit
//
void AlignofExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}