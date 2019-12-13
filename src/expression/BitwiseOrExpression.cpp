#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
BitwiseOrExpression::BitwiseOrExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
BitwiseOrExpression* BitwiseOrExpression::clone() const {
  return new BitwiseOrExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void BitwiseOrExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct BitwiseOrOperator {
  static inline ConstantExpression* evaluate(T left, T right);
};

template<typename T> inline ConstantExpression* BitwiseOrOperator<T>::evaluate(T left, T right) {
  return new ConstantExpression((T)(left | right));
}

// Floating point types are invalid
template<>
inline ConstantExpression* BitwiseOrOperator<C_FLOAT>::evaluate(C_FLOAT left, C_FLOAT right) {
  return nullptr;
}
template<>
inline ConstantExpression* BitwiseOrOperator<C_DOUBLE>::evaluate(C_DOUBLE left, C_DOUBLE right) {
  return nullptr;
}
template<>
inline ConstantExpression* BitwiseOrOperator<C_LONGDOUBLE>::evaluate(C_LONGDOUBLE left,
                                                                     C_LONGDOUBLE right) {
  return nullptr;
}

const BinaryOperatorEvaluator& BitwiseOrExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<BitwiseOrOperator> evaluator;
  return evaluator;
}
