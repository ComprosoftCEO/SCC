#include <Expression.h>

//
// Constructor
//
GreaterThanOrEqualExpression::GreaterThanOrEqualExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
