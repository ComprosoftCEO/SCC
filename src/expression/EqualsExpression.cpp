#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
EqualsExpression::EqualsExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
EqualsExpression* EqualsExpression::clone() const {
  return new EqualsExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void EqualsExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct EqualsOperator {
  static inline ConstantExpression* evaluate(T left, T right) {
    return new ConstantExpression((C_INT)(left == right));
  }
};

const BinaryOperatorEvaluator& EqualsExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<EqualsOperator> evaluator;
  return evaluator;
}
