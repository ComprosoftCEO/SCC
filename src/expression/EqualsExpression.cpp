#include <Expression.h>

//
// Constructor
//
EqualsExpression::EqualsExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
