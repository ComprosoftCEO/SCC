#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
StringExpression::StringExpression(const std::string& str): str(str) {}

//
// Getters
//
const std::string& StringExpression::get_string() const {
  return this->str;
}

//
// Clone
//
StringExpression* StringExpression::clone() const {
  return new StringExpression(this->str);
}

//
// Visit
//
void StringExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}
