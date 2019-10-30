#include <Expression.h>

//
// Constructor
//
ConditionalExpression::ConditionalExpression(Expression* condition, Expression* cond_true,
                                             Expression* cond_false):
  condition(condition), cond_true(cond_true), cond_false(cond_false) {}
