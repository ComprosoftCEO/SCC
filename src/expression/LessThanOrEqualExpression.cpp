#include <Expression.h>

//
// Constructor
//
LessThanOrEqualExpression::LessThanOrEqualExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
