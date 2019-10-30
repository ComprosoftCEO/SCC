#include <Expression.h>

//
// Constructor
//
MultiplicationExpression::MultiplicationExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
