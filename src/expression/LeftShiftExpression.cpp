#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
LeftShiftExpression::LeftShiftExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
LeftShiftExpression* LeftShiftExpression::clone() const {
  return new LeftShiftExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void LeftShiftExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct LeftShiftOperator {
  static inline ConstantExpression* evaluate(T left, T right);
};

template<typename T> inline ConstantExpression* LeftShiftOperator<T>::evaluate(T left, T right) {
  return new ConstantExpression((T)(left << right));
}

// Float types are invalid
template<>
inline ConstantExpression* LeftShiftOperator<C_FLOAT>::evaluate(C_FLOAT left, C_FLOAT right) {
  return nullptr;
}
template<>
inline ConstantExpression* LeftShiftOperator<C_DOUBLE>::evaluate(C_DOUBLE left, C_DOUBLE right) {
  return nullptr;
}
template<>
inline ConstantExpression* LeftShiftOperator<C_LONGDOUBLE>::evaluate(C_LONGDOUBLE left,
                                                                     C_LONGDOUBLE right) {
  return nullptr;
}

const BinaryOperatorEvaluator& LeftShiftExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<LeftShiftOperator> evaluator;
  return evaluator;
}
