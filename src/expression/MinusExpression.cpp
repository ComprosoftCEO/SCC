#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
MinusExpression::MinusExpression(Expression* expr): UnaryExpression(expr) {}

//
// Clone
//
MinusExpression* MinusExpression::clone() const {
  return new MinusExpression(this->expr->clone());
}

//
// Visit
//
void MinusExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get unary operator
//
template<typename T> struct MinusOperator {
  static ConstantExpression* evaluate(T input) {
    return new ConstantExpression((T)(-input));
  }
};

const UnaryOperatorEvaluator& MinusExpression::get_evaluator() const {
  static const ConcreteUnaryOperatorEvaluator<MinusOperator> evaluator;
  return evaluator;
}
