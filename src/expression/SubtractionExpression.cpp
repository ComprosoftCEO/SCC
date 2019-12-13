#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
SubtractionExpression::SubtractionExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
SubtractionExpression* SubtractionExpression::clone() const {
  return new SubtractionExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void SubtractionExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct SubtractionOperator {
  static inline ConstantExpression* evaluate(T left, T right) {
    return new ConstantExpression((T)(left - right));
  }
};

const BinaryOperatorEvaluator& SubtractionExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<SubtractionOperator> evaluator;
  return evaluator;
}
