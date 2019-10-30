#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
ConditionalExpression::ConditionalExpression(Expression* condition, Expression* cond_true,
                                             Expression* cond_false):
  condition(condition), cond_true(cond_true), cond_false(cond_false) {}

//
// Clone
//
Expression* ConditionalExpression::clone() const {
  return new ConditionalExpression(this->condition->clone(), this->cond_true->clone(),
                                   this->cond_false->clone());
}

//
// Visit
//
void ConditionalExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}