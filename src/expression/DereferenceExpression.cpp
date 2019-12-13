#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
DereferenceExpression::DereferenceExpression(Expression* expr): expr(expr) {}

//
// Destructor
//
DereferenceExpression::~DereferenceExpression() {
  delete (this->expr);
}

//
// Getters
//
Expression* DereferenceExpression::get_expression() const {
  return this->expr;
}

//
// Clone
//
DereferenceExpression* DereferenceExpression::clone() const {
  return new DereferenceExpression(Expression::clone(this->expr));
}

//
// Visit
//
void DereferenceExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}