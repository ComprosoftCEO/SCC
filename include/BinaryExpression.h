#ifndef BINARY_EXPRESSION_HEADER
#define BINARY_EXPRESSION_HEADER

#include <Expression.h>

/**
 * Bianry operators, like +, -, *, /, %, etc
 */
class BinaryExpression: public Expression {

public:
  BinaryExpression(Expression* left, Expression* right);

  ConstantValue evaluate();

private:
  // Compute a stored binary operator at runtime
  virtual ConstantValue binary_operator(ConstantValue left, ConstantValue right) = 0;

private:
  Expression* left;
  Expression* right;
};

#endif /* Binary Expression Header Included */