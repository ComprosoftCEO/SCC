#include <Expression.h>

//
// Constructor
//
FunctionCallExpression::FunctionCallExpression(Expression* expr): expr(expr) {}

FunctionCallExpression::FunctionCallExpression(Expression* expr,
                                               const std::vector<Expression*>& parameters):
  expr(expr), parameters(parameters) {}
