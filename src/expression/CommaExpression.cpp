#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
CommaExpression::CommaExpression() {}

CommaExpression::CommaExpression(const std::vector<Expression*>& expr_list): expr_list(expr_list) {}

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

//
// Clone
//
Expression* CommaExpression::clone() const {
  std::vector<Expression*> new_list;
  for (auto e: this->expr_list) { new_list.push_back(e->clone()); }
  return new CommaExpression(new_list);
}

//
// Visit
//
void CommaExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}
