#include <Expression.h>

//
// Constructor
//
NotEqualsExpression::NotEqualsExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
