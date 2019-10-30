#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
AssignmentExpression::AssignmentExpression(Expression* dest, Expression* src):
  dest(dest), src(src) {}

//
// Clone
//
AssignmentExpression* AssignmentExpression::clone() const {
  return new AssignmentExpression(this->dest->clone(), this->src->clone());
}

//
// Visit
//
void AssignmentExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}
