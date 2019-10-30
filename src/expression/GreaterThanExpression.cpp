#include <Expression.h>

//
// Constructor
//
GreaterThanExpression::GreaterThanExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
