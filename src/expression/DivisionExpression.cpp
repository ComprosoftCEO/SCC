#include <Expression.h>

//
// Constructor
//
DivisionExpression::DivisionExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
