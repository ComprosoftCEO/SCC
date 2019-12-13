#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
DivisionExpression::DivisionExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
DivisionExpression* DivisionExpression::clone() const {
  return new DivisionExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void DivisionExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct DivisionOperator {
  static inline ConstantExpression* evaluate(T left, T right) {
    if (right == 0) { return nullptr; }
    return new ConstantExpression((T)(left / right));
  }
};

const BinaryOperatorEvaluator& DivisionExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<DivisionOperator> evaluator;
  return evaluator;
}
