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
  for (auto e: this->expr_list) { delete (e); }
}

//
// Add an expression to the list
//
void CommaExpression::add_expression(Expression* expr) {
  this->expr_list.push_back(expr);
}

//
// Get list of expressions
//
const std::vector<Expression*>& CommaExpression::get_expression_list() const {
  return this->expr_list;
}

//
// Clone
//
CommaExpression* CommaExpression::clone() const {
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
