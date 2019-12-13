#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
RightShiftExpression::RightShiftExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
RightShiftExpression* RightShiftExpression::clone() const {
  return new RightShiftExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void RightShiftExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct RightShiftOperator {
  static inline ConstantExpression* evaluate(T left, T right);
};

template<typename T> inline ConstantExpression* RightShiftOperator<T>::evaluate(T left, T right) {
  return new ConstantExpression((T)(left >> right));
}

// Float types throw an exception
template<>
inline ConstantExpression* RightShiftOperator<C_FLOAT>::evaluate(C_FLOAT left, C_FLOAT right) {
  return nullptr;
}
template<>
inline ConstantExpression* RightShiftOperator<C_DOUBLE>::evaluate(C_DOUBLE left, C_DOUBLE right) {
  return nullptr;
}
template<>
inline ConstantExpression* RightShiftOperator<C_LONGDOUBLE>::evaluate(C_LONGDOUBLE left,
                                                                      C_LONGDOUBLE right) {
  return nullptr;
}

const BinaryOperatorEvaluator& RightShiftExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<RightShiftOperator> evaluator;
  return evaluator;
}
