#include <Expression.h>

//
// Constructor
//
LeftShiftExpression::LeftShiftExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
