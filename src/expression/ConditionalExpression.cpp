#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
ConditionalExpression::ConditionalExpression(Expression* condition, Expression* cond_true,
                                             Expression* cond_false):
  condition(condition), cond_true(cond_true), cond_false(cond_false) {}

//
// Destructor
//
ConditionalExpression::~ConditionalExpression() {
  delete (this->condition);
  delete (this->cond_true);
  delete (this->cond_false);
}

//
// Getters
//
Expression* ConditionalExpression::get_condition() const {
  return this->condition;
}

Expression* ConditionalExpression::get_true_expression() const {
  return this->cond_true;
}

Expression* ConditionalExpression::get_false_expression() const {
  return this->cond_false;
}

//
// Clone
//
ConditionalExpression* ConditionalExpression::clone() const {
  return new ConditionalExpression(this->condition->clone(), this->cond_true->clone(),
                                   this->cond_false->clone());
}

//
// Visit
//
void ConditionalExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}