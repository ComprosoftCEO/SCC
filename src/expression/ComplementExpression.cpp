#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
ComplementExpression::ComplementExpression(Expression* expr): UnaryExpression(expr) {}

//
// Clone
//
ComplementExpression* ComplementExpression::clone() const {
  return new ComplementExpression(this->expr->clone());
}

//
// Visit
//
void ComplementExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Unary operator classes
//
template<typename T> struct ComplementOperator {
  static inline ConstantExpression* evaluate(T input);
};

template<typename T> inline ConstantExpression* ComplementOperator<T>::evaluate(T input) {
  return new ConstantExpression((T)(~input));
}

// Float types throw an exception
template<> inline ConstantExpression* ComplementOperator<C_FLOAT>::evaluate(C_FLOAT input) {
  return nullptr;
}
template<> inline ConstantExpression* ComplementOperator<C_DOUBLE>::evaluate(C_DOUBLE input) {
  return nullptr;
}
template<>
inline ConstantExpression* ComplementOperator<C_LONGDOUBLE>::evaluate(C_LONGDOUBLE input) {
  return nullptr;
}

//
// Get unary operator
//
const UnaryOperatorEvaluator& ComplementExpression::get_evaluator() const {
  static const ConcreteUnaryOperatorEvaluator<ComplementOperator> evaluator;
  return evaluator;
}
