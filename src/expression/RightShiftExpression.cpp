#include <Expression.h>

//
// Constructor
//
RightShiftExpression::RightShiftExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
