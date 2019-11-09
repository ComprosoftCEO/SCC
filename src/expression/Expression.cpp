#include <Expression.h>

//
// Static clone method
//
Expression* Expression::clone(Expression* expr) {
  return expr != nullptr ? expr->clone() : nullptr;
}
