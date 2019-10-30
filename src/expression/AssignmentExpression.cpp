#include <Expression.h>

//
// Constructor
//
AssignmentExpression::AssignmentExpression(Expression* dest, Expression* src):
  dest(dest), src(src) {}
