#include <Expression.h>

//
// Constructor
//
LogicalAndExpression::LogicalAndExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
