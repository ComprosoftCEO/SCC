#include <Expression.h>

//
// Constructor
//
LogicalOrExpression::LogicalOrExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
