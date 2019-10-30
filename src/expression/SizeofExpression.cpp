#include <Expression.h>
#include <Visitor.h>

//
// Constructor.h
//
SizeofExpression::SizeofExpression(Expression* expr): UnaryExpression(expr) {}

//
// Clone
//
SizeofExpression* SizeofExpression::clone() const {
  return new SizeofExpression(this->expr->clone());
}

//
// Visit
//
void SizeofExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}