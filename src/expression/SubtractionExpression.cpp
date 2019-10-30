#include <Expression.h>

//
// Constructor
//
SubtractionExpression::SubtractionExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}
