#ifndef EXPRESSION_HEADER
#define EXPRESSION_HEADER

#include <ConstantValue.h>
#include <string>
#include <vector>

// Forward declare classes
class ExpressionVisitor;

class Expression;
class AssignmentExpression;
class BinaryExpression;
class ConstantExpression;

class Expression {

public:
  virtual ~Expression() = default;

  // Attempt to do compile-time evaluation of the expression
  //  Throws an exception on error
  //  virtual ConstantValue evaluate() = 0;

  //  virtual void visit(ExpressionVisitor& visitor) = 0;
};

/**
 * Comma-separated list of expressions
 */
class CommaExpression: public Expression {

public:
  CommaExpression();

  void add_expression(Expression* expr);

private:
  std::vector<Expression*> expr_list;
};

/**
 * Expression that stores an assignment
 */
class AssignmentExpression: public Expression {

public:
  AssignmentExpression(Expression* dest, Expression* src);

private:
  Expression* dest;
  Expression* src;
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
class IdentifierExpression: public Expression {

public:
  IdentifierExpression(const std::string& identifier);

  // Get the stored identifier
  const std::string& get_identifier() const;

private:
  std::string identifier;
};

/**
 * Represents calling a function
 */
class FunctionCallExpression: public Expression {

public:
  FunctionCallExpression(Expression* expr); // No arguments
  FunctionCallExpression(Expression* expr, const std::vector<Expression*>& parameters);

private:
  Expression* expr;
  std::vector<Expression*> parameters;
};

/**
 * Unary operators, like -, +, and !
 */
class UnaryExpression: public Expression {

public:
  UnaryExpression(Expression* expr);

  // ConstantValue evaluate();

private:
  //  virtual ConstantValue unary_operator(ConstantValue value) = 0;

private:
  Expression* expr;
};

/**
 * Putting the minus symbol in front of a number
 */
class MinusExpression: public UnaryExpression {

public:
  MinusExpression(Expression* expr);
};

/**
 * Boolean not (!)
 */
class NotExpression: public UnaryExpression {

public:
  NotExpression(Expression* expr);
};

/**
 * Bitwise Complement (~)
 */
class ComplementExpression: public UnaryExpression {

public:
  ComplementExpression(Expression* expr);
};

/**
 * Dereferencing a pointer
 */
class DereferenceExpression: public UnaryExpression {

public:
  DereferenceExpression(Expression* expr);
};

/**
 * Get the address of a given variable
 */
class AddressOfExpression: public UnaryExpression {

public:
  AddressOfExpression(Expression* expr);
};

/**
 * Get the size of a variable
 */
class SizeofExpression: public UnaryExpression {

public:
  SizeofExpression(Expression* expr);
};

/**
 * Get the alignment of a variable
 */
class AlignofExpression: public UnaryExpression {

public:
  AlignofExpression(Expression* expr);
};

/**
 * Bianry operators, like +, -, *, /, %, etc
 */
class BinaryExpression: public Expression {

public:
  BinaryExpression(Expression* left, Expression* right);

  ConstantValue evaluate();

private:
  // Compute a stored binary operator at runtime
  // virtual ConstantValue binary_operator(ConstantValue left, ConstantValue right) = 0;

private:
  Expression* left;
  Expression* right;
};

/**
 * Accessing element in an array or from a pointer
 */
class BracketExpression: public BinaryExpression {

public:
  BracketExpression(Expression* expr, Expression* index);
};

/**
 * Store an addition operator (+)
 */
class AdditionExpression: public BinaryExpression {

public:
  AdditionExpression(Expression* left, Expression* right);
};

/**
 * Store a subtraction operator (-)
 */
class SubtractionExpression: public BinaryExpression {

public:
  SubtractionExpression(Expression* left, Expression* right);
};

/**
 * Store a multiplication operator (*)
 */
class MultiplicationExpression: public BinaryExpression {

public:
  MultiplicationExpression(Expression* left, Expression* right);
};

/**
 * Store a division operator (/)
 */
class DivisionExpression: public BinaryExpression {

public:
  DivisionExpression(Expression* left, Expression* right);
};

/**
 * Store a modulus expression (%)
 */
class ModulusExpression: public BinaryExpression {

public:
  ModulusExpression(Expression* left, Expression* right);
};

/**
 * Store a left bit shift expression (<<)
 */
class LeftShiftExpression: public BinaryExpression {

public:
  LeftShiftExpression(Expression* left, Expression* right);
};

/**
 * Store a right bit shift expression
 */
class RightShiftExpression: public BinaryExpression {

public:
  RightShiftExpression(Expression* left, Expression* right);
};

/**
 * Test for less than (<)
 */
class LessThanExpression: public BinaryExpression {

public:
  LessThanExpression(Expression* left, Expression* right);
};

/**
 * Test for greater than (>)
 */
class GreaterThanExpression: public BinaryExpression {

public:
  GreaterThanExpression(Expression* left, Expression* right);
};

/**
 * Test for less than or equal to (<=)
 */
class LessThanOrEqualExpression: public BinaryExpression {

public:
  LessThanOrEqualExpression(Expression* left, Expression* right);
};

/**
 * Test for greater than or equal to (>=)
 */
class GreaterThanOrEqualExpression: public BinaryExpression {

public:
  GreaterThanOrEqualExpression(Expression* left, Expression* right);
};

/**
 * Test for equality (==)
 */
class EqualsExpression: public BinaryExpression {

public:
  EqualsExpression(Expression* left, Expression* right);
};

/**
 * Test for inequality (!=)
 */
class NotEqualsExpression: public BinaryExpression {

public:
  NotEqualsExpression(Expression* left, Expression* right);
};

/**
 * Bitwise and (&)
 */
class BitwiseAndExpression: public BinaryExpression {

public:
  BitwiseAndExpression(Expression* left, Expression* right);
};

/**
 * Bitwise or expression (|)
 */
class BitwiseOrExpression: public BinaryExpression {

public:
  BitwiseOrExpression(Expression* left, Expression* right);
};

/**
 * Bitwise exclusive or (^)
 */
class BitwiseXorExpression: public BinaryExpression {

public:
  BitwiseXorExpression(Expression* left, Expression* right);
};

/**
 * And expression used in an if statement (&&)
 */
class LogicalAndExpression: public BinaryExpression {

public:
  LogicalAndExpression(Expression* left, Expression* right);
};

/**
 * Or logical expression used in an if statement (||)
 */
class LogicalOrExpression: public BinaryExpression {

public:
  LogicalOrExpression(Expression* left, Expression* right);
};

/**
 * Stores expressions of the form (a ? b : c)
 */
class ConditionalExpression: public Expression {

public:
  ConditionalExpression(Expression* condition, Expression* cond_true, Expression* cond_false);

private:
  Expression* condition;
  Expression* cond_true;
  Expression* cond_false;
};

#endif /* Expression Header Included */