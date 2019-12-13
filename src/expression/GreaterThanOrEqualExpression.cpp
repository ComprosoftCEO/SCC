#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
GreaterThanOrEqualExpression::GreaterThanOrEqualExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
GreaterThanOrEqualExpression* GreaterThanOrEqualExpression::clone() const {
  return new GreaterThanOrEqualExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void GreaterThanOrEqualExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct GreaterThanOrEqualOperator {
  static inline ConstantExpression* evaluate(T left, T right) {
    return new ConstantExpression((C_INT)(left >= right));
  }
};

const BinaryOperatorEvaluator& GreaterThanOrEqualExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<GreaterThanOrEqualOperator> evaluator;
  return evaluator;
}
