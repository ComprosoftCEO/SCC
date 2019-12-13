#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
ModulusExpression::ModulusExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
ModulusExpression* ModulusExpression::clone() const {
  return new ModulusExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void ModulusExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct ModulusOperator {
  static inline ConstantExpression* evaluate(T left, T right);
};

template<typename T> inline ConstantExpression* ModulusOperator<T>::evaluate(T left, T right) {
  if (right == 0) { return nullptr; }
  return new ConstantExpression((T)(left % right));
}

// Float types are invalid
template<>
inline ConstantExpression* ModulusOperator<C_FLOAT>::evaluate(C_FLOAT left, C_FLOAT right) {
  return nullptr;
}
template<>
inline ConstantExpression* ModulusOperator<C_DOUBLE>::evaluate(C_DOUBLE left, C_DOUBLE right) {
  return nullptr;
}
template<>
inline ConstantExpression* ModulusOperator<C_LONGDOUBLE>::evaluate(C_LONGDOUBLE left,
                                                                   C_LONGDOUBLE right) {
  return nullptr;
}

const BinaryOperatorEvaluator& ModulusExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<ModulusOperator> evaluator;
  return evaluator;
}
