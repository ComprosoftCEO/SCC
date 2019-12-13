#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
MultiplicationExpression::MultiplicationExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
MultiplicationExpression* MultiplicationExpression::clone() const {
  return new MultiplicationExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void MultiplicationExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct MultiplicationOperator {
  static inline ConstantExpression* evaluate(T left, T right) {
    return new ConstantExpression((T)(left * right));
  }
};

const BinaryOperatorEvaluator& MultiplicationExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<MultiplicationOperator> evaluator;
  return evaluator;
}
