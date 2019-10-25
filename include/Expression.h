#ifndef EXPRESSION_HEADER
#define EXPRESSION_HEADER

#include <ConstantValue.h>

// Forward declare classes
class ExpressionVisitor;

class Expression;
class BinaryExpression;
class ConstantExpression;

class Expression {

public:
  virtual ~Expression() = default;

  // Attempt to do compile-time evaluation of the expression
  //  Throws an exception on error
  virtual ConstantValue evaluate() = 0;

  virtual void visit(ExpressionVisitor& visitor) = 0;
};

/**
 * Casting from one data type to another
 */
class CastExpression: public Expression {};

/**
 * Represents a string literal, like "Hello World!"
 */
class StringExpression: public Expression {};

/**
 * Expression that represents a variable, like "i", "j", or "k"
 */
class VariableExpression: public Expression {};

#endif /* Expression Header Included */