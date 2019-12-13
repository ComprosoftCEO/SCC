#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
LessThanOrEqualExpression::LessThanOrEqualExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
LessThanOrEqualExpression* LessThanOrEqualExpression::clone() const {
  return new LessThanOrEqualExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void LessThanOrEqualExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct LessThanOrEqualOperator {
  static inline ConstantExpression* evaluate(T left, T right) {
    return new ConstantExpression((C_INT)(left <= right));
  }
};

const BinaryOperatorEvaluator& LessThanOrEqualExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<LessThanOrEqualOperator> evaluator;
  return evaluator;
}
