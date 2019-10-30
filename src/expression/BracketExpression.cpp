#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
BracketExpression::BracketExpression(Expression* expr, Expression* index):
  expr(expr), index(index) {}

//
// Destructor
//
BracketExpression::~BracketExpression() {
  delete (this->expr);
  delete (this->index);
}

//
// Getters
//
Expression* BracketExpression::get_expression() const {
  return this->expr;
}

Expression* BracketExpression::get_index() const {
  return this->index;
}

//
// Clone
//
BracketExpression* BracketExpression::clone() const {
  return new BracketExpression(this->expr->clone(), this->index->clone());
}

//
// Visit
//
void BracketExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}
