#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
NotEqualsExpression::NotEqualsExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
NotEqualsExpression* NotEqualsExpression::clone() const {
  return new NotEqualsExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void NotEqualsExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct NotEqualsOperator {
  static inline ConstantExpression* evaluate(T left, T right) {
    return new ConstantExpression((C_INT)(left != right));
  }
};

const BinaryOperatorEvaluator& NotEqualsExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<NotEqualsOperator> evaluator;
  return evaluator;
}
