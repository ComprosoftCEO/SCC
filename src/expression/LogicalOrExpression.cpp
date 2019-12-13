#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
LogicalOrExpression::LogicalOrExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
LogicalOrExpression* LogicalOrExpression::clone() const {
  return new LogicalOrExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void LogicalOrExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct LogicalOrOperator {
  static inline ConstantExpression* evaluate(T left, T right) {
    return new ConstantExpression((C_INT)(left || right));
  }
};

const BinaryOperatorEvaluator& LogicalOrExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<LogicalOrOperator> evaluator;
  return evaluator;
}
