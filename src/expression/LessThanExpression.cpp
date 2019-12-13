#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
LessThanExpression::LessThanExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
LessThanExpression* LessThanExpression::clone() const {
  return new LessThanExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void LessThanExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct LessThanOperator {
  static inline ConstantExpression* evaluate(T left, T right) {
    return new ConstantExpression((C_INT)(left < right));
  }
};

const BinaryOperatorEvaluator& LessThanExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<LessThanOperator> evaluator;
  return evaluator;
}
