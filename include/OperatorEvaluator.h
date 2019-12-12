#ifndef OPERATOR_EVALUATOR_HEADER
#define OPERATOR_EVALUATOR_HEADER

#include <CTypes.h>

class ConstantExpression;

/**
 * @class UnaryOperatorEvaluator
 * Interface for evaluating a generic unary operator
 */
class UnaryOperatorEvaluator {

public:
  virtual ~UnaryOperatorEvaluator() = default;

  // Evaluate using the underlying operator
  //  If the operator is not valud for the type or an error occurs, return nullptr
  ConstantExpression* evaluate(ConstantExpression* expr) const;

private:
  virtual ConstantExpression* do_operation(C_INT expr) const        = 0;
  virtual ConstantExpression* do_operation(C_UINT expr) const       = 0;
  virtual ConstantExpression* do_operation(C_LONG expr) const       = 0;
  virtual ConstantExpression* do_operation(C_ULONG expr) const      = 0;
  virtual ConstantExpression* do_operation(C_LONGLONG expr) const   = 0;
  virtual ConstantExpression* do_operation(C_ULONGLONG expr) const  = 0;
  virtual ConstantExpression* do_operation(C_FLOAT expr) const      = 0;
  virtual ConstantExpression* do_operation(C_DOUBLE expr) const     = 0;
  virtual ConstantExpression* do_operation(C_LONGDOUBLE expr) const = 0;
};

/**
 * @class BinaryOperatorEvaluator
 * Interface for evaluating a generic binary operator
 */
class BinaryOperatorEvaluator {

public:
  virtual ~BinaryOperatorEvaluator() = default;

  // Evaluate using the underlying operator
  //  If the operator is not valud for the type or an error occurs, return nullptr
  ConstantExpression* evaluate(ConstantExpression* left, ConstantExpression* right) const;

private:
  virtual ConstantExpression* do_operation(C_INT left, C_INT right) const               = 0;
  virtual ConstantExpression* do_operation(C_UINT left, C_UINT right) const             = 0;
  virtual ConstantExpression* do_operation(C_LONG left, C_LONG right) const             = 0;
  virtual ConstantExpression* do_operation(C_ULONG left, C_ULONG right) const           = 0;
  virtual ConstantExpression* do_operation(C_LONGLONG left, C_LONGLONG right) const     = 0;
  virtual ConstantExpression* do_operation(C_ULONGLONG left, C_ULONGLONG right) const   = 0;
  virtual ConstantExpression* do_operation(C_FLOAT left, C_FLOAT right) const           = 0;
  virtual ConstantExpression* do_operation(C_DOUBLE left, C_DOUBLE right) const         = 0;
  virtual ConstantExpression* do_operation(C_LONGDOUBLE left, C_LONGDOUBLE right) const = 0;
};

// ========= Concrete versions ============

/**
 * @class ConcreteUnaryOperatorEvaluator
 * Create a concrete UnaryOperatorEvaluator using a template lambda
 *
 * FUNC must be a template class with one static method:
 *   static ConstantExpression* evaluate(T input);
 */
// clang-format off
template<template<typename> typename FUNC>
class ConcreteUnaryOperatorEvaluator final: public UnaryOperatorEvaluator {

private:
  ConstantExpression* do_operation(C_INT expr) const         { return FUNC<C_INT>::evaluate(expr); }
  ConstantExpression* do_operation(C_UINT expr) const        { return FUNC<C_UINT>::evaluate(expr); }
  ConstantExpression* do_operation(C_LONG expr) const        { return FUNC<C_LONG>::evaluate(expr); }
  ConstantExpression* do_operation(C_ULONG expr) const       { return FUNC<C_ULONG>::evaluate(expr); }
  ConstantExpression* do_operation(C_LONGLONG expr) const    { return FUNC<C_LONGLONG>::evaluate(expr); }
  ConstantExpression* do_operation(C_ULONGLONG expr) const   { return FUNC<C_ULONGLONG>::evaluate(expr); }
  ConstantExpression* do_operation(C_FLOAT expr) const       { return FUNC<C_FLOAT>::evaluate(expr); }
  ConstantExpression* do_operation(C_DOUBLE expr) const      { return FUNC<C_DOUBLE>::evaluate(expr); }
  ConstantExpression* do_operation(C_LONGDOUBLE expr) const  { return FUNC<C_LONGDOUBLE>::evaluate(expr); }
};

/**
 * @class ConcreteBinaryOperatorEvaluator
 * Create a concrete BinaryOperatorEvaluator using a template lambda
 *
 * FUNC must be a template class with one static method:
 *   static ConstantExpression* evaluate(T left, T right);
 */
template<template<typename> typename FUNC>
class ConcreteBinaryOperatorEvaluator final: public BinaryOperatorEvaluator {

private:
  ConstantExpression* do_operation(C_INT left, C_INT right) const               { return FUNC<C_INT>::evaluate(left, right); }
  ConstantExpression* do_operation(C_UINT left, C_UINT right) const             { return FUNC<C_UINT>::evaluate(left, right); }
  ConstantExpression* do_operation(C_LONG left, C_LONG right) const             { return FUNC<C_LONG>::evaluate(left, right); }
  ConstantExpression* do_operation(C_ULONG left, C_ULONG right) const           { return FUNC<C_ULONG>::evaluate(left, right); }
  ConstantExpression* do_operation(C_LONGLONG left, C_LONGLONG right) const     { return FUNC<C_LONGLONG>::evaluate(left, right); }
  ConstantExpression* do_operation(C_ULONGLONG left, C_ULONGLONG right) const   { return FUNC<C_ULONGLONG>::evaluate(left, right); }
  ConstantExpression* do_operation(C_FLOAT left, C_FLOAT right) const           { return FUNC<C_FLOAT>::evaluate(left, right); }
  ConstantExpression* do_operation(C_DOUBLE left, C_DOUBLE right) const         { return FUNC<C_DOUBLE>::evaluate(left, right); }
  ConstantExpression* do_operation(C_LONGDOUBLE left, C_LONGDOUBLE right) const { return FUNC<C_LONGDOUBLE>::evaluate(left, right); }
};
// clang-format on

#endif /* Operator Evaluator Header Included */