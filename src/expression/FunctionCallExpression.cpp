#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
FunctionCallExpression::FunctionCallExpression(Expression* expr): expr(expr) {}

FunctionCallExpression::FunctionCallExpression(Expression* expr,
                                               const std::vector<Expression*>& parameters):
  expr(expr), parameters(parameters) {}

//
// Clone
//
FunctionCallExpression* FunctionCallExpression::clone() const {
  std::vector<Expression*> new_list;
  for (auto e: this->parameters) { new_list.push_back(e->clone()); }
  return new FunctionCallExpression(this->expr->clone(), new_list);
}

//
// Visit
//
void FunctionCallExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}