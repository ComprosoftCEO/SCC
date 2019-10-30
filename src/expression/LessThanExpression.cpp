#include <Expression.h>

//
// Constructor
//
LessThanExpression::LessThanExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
