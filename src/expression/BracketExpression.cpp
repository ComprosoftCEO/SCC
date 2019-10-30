#include <Expression.h>

//
// Constructor
//
BracketExpression::BracketExpression(Expression* expr, Expression* index):
  expr(expr), index(index) {}
