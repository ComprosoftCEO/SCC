#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
BitwiseXorExpression::BitwiseXorExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
BitwiseXorExpression* BitwiseXorExpression::clone() const {
  return new BitwiseXorExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void BitwiseXorExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct BitwiseXorOperator {
  static inline ConstantExpression* evaluate(T left, T right);
};

template<typename T> inline ConstantExpression* BitwiseXorOperator<T>::evaluate(T left, T right) {
  return new ConstantExpression((T)(left ^ right));
}

// Floating point types are invalid
template<>
inline ConstantExpression* BitwiseXorOperator<C_FLOAT>::evaluate(C_FLOAT left, C_FLOAT right) {
  return nullptr;
}
template<>
inline ConstantExpression* BitwiseXorOperator<C_DOUBLE>::evaluate(C_DOUBLE left, C_DOUBLE right) {
  return nullptr;
}
template<>
inline ConstantExpression* BitwiseXorOperator<C_LONGDOUBLE>::evaluate(C_LONGDOUBLE left,
                                                                      C_LONGDOUBLE right) {
  return nullptr;
}

const BinaryOperatorEvaluator& BitwiseXorExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<BitwiseXorOperator> evaluator;
  return evaluator;
}
