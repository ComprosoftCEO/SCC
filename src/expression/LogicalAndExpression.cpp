#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
LogicalAndExpression::LogicalAndExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
LogicalAndExpression* LogicalAndExpression::clone() const {
  return new LogicalAndExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void LogicalAndExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct LogicalAndOperator {
  static inline ConstantExpression* evaluate(T left, T right) {
    return new ConstantExpression((C_INT)(left && right));
  }
};

const BinaryOperatorEvaluator& LogicalAndExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<LogicalAndOperator> evaluator;
  return evaluator;
}
