#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
NotExpression::NotExpression(Expression* expr): UnaryExpression(expr) {}

//
// Clone
//
NotExpression* NotExpression::clone() const {
  return new NotExpression(this->expr->clone());
}

//
// Visit
//
void NotExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get unary operator
//
template<typename T> struct NotOperator {
  static inline ConstantExpression* evaluate(T input) {
    return new ConstantExpression((C_INT)(!input));
  }
};

const UnaryOperatorEvaluator& NotExpression::get_evaluator() const {
  static const ConcreteUnaryOperatorEvaluator<NotOperator> evaluator;
  return evaluator;
}
