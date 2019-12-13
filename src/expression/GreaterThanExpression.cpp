#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
GreaterThanExpression::GreaterThanExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
GreaterThanExpression* GreaterThanExpression::clone() const {
  return new GreaterThanExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void GreaterThanExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct GreaterThanOperator {
  static inline ConstantExpression* evaluate(T left, T right) {
    return new ConstantExpression((C_INT)(left > right));
  }
};

const BinaryOperatorEvaluator& GreaterThanExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<GreaterThanOperator> evaluator;
  return evaluator;
}
