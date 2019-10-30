#include <Expression.h>

//
// Constructor
//
CommaExpression::CommaExpression() {}

//
// Destructor
//
CommaExpression::~CommaExpression() {
  for (auto it: this->expr_list) { delete (it); }
}

//
// Add an expression to the list
//
void CommaExpression::add_expression(Expression* expr) {
  this->expr_list.push_back(expr);
}
