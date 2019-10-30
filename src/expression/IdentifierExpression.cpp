#include <Expression.h>

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
