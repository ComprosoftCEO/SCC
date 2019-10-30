#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
IdentifierExpression::IdentifierExpression(const std::string& identifier): identifier(identifier) {}

//
// Get identifier
//
const std::string& IdentifierExpression::get_identifier() const {
  return this->identifier;
}

//
// Clone
//
Expression* IdentifierExpression::clone() const {
  return new IdentifierExpression(this->identifier);
}

//
// Visit
//
void IdentifierExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}