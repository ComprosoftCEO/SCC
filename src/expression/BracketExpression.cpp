#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
BracketExpression::BracketExpression(Expression* expr, Expression* index):
  expr(expr), index(index) {}

//
// Clone
//
Expression* BracketExpression::clone() const {
  return new BracketExpression(this->expr->clone(), this->index->clone());
}

//
// Visit
//
void BracketExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}
