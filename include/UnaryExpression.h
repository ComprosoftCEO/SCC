#ifndef UNARY_EXPRESSION_HEADER
#define UNARY_EXPRESSION_HEADER

#include <Expression.h>

/**
 * Unary operators, like -, +, and !
 */
class UnaryExpression: public Expression {

public:
  UnaryExpression(Expression* expr);

  ConstantValue evaluate();

private:
  virtual ConstantValue unary_operator(ConstantValue value) = 0;

private:
  Expression* expr;
};

/**
 * Putting the plus symbol in front of a number
 */
class UnaryPlusExpression: public UnaryExpression {

public:
  UnaryPlusExpression(Expression* expr);

private:
  ConstantValue unary_operator(ConstantValue value);
};

/**
 * Putting the minus symbol in front of a number
 */
class UnaryMinusExpression: public UnaryExpression {

public:
  UnaryMinusExpression(Expression* expr);

private:
  ConstantValue unary_operator(ConstantValue value);
};

/**
 * Boolean not (!)
 */
class NotExpression: public UnaryExpression {

public:
  NotExpression(Expression* expr);

private:
  ConstantValue unary_operator(ConstantValue value);
};

/**
 * Bitwise Complement (~)
 */
class ComplementExpression: public UnaryExpression {

public:
  ComplementExpression(Expression* expr);

private:
  ConstantValue unary_operator(ConstantValue value);
};

#endif /* Unary Expression Header Included */