#include <Expression.h>

//
// Constructor
//
AdditionExpression::AdditionExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
