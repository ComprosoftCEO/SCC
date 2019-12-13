#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
AddressOfExpression::AddressOfExpression(Expression* expr): expr(expr) {}

//
// Destructor
//
AddressOfExpression::~AddressOfExpression() {
  delete (this->expr);
}

//
// Getters
//
Expression* AddressOfExpression::get_expression() const {
  return this->expr;
}

//
// Clone
//
AddressOfExpression* AddressOfExpression::clone() const {
  return new AddressOfExpression(Expression::clone(this->expr));
}

//
// Visit
//
void AddressOfExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}