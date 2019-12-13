#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
BitwiseAndExpression::BitwiseAndExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
BitwiseAndExpression* BitwiseAndExpression::clone() const {
  return new BitwiseAndExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void BitwiseAndExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct BitwiseAndOperator {
  static inline ConstantExpression* evaluate(T left, T right);
};

template<typename T> inline ConstantExpression* BitwiseAndOperator<T>::evaluate(T left, T right) {
  return new ConstantExpression((T)(left & right));
}

// Floating point types are invalid
template<>
inline ConstantExpression* BitwiseAndOperator<C_FLOAT>::evaluate(C_FLOAT left, C_FLOAT right) {
  return nullptr;
}
template<>
inline ConstantExpression* BitwiseAndOperator<C_DOUBLE>::evaluate(C_DOUBLE left, C_DOUBLE right) {
  return nullptr;
}
template<>
inline ConstantExpression* BitwiseAndOperator<C_LONGDOUBLE>::evaluate(C_LONGDOUBLE left,
                                                                      C_LONGDOUBLE right) {
  return nullptr;
}

const BinaryOperatorEvaluator& BitwiseAndExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<BitwiseAndOperator> evaluator;
  return evaluator;
}
