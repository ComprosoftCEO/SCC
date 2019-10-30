#ifndef EXPRESSION_HEADER
#define EXPRESSION_HEADER

#include <ConstantValue.h>
#include <string>
#include <vector>

// Forward declare classes
class ExpressionVisitor;

class Expression {

public:
  virtual ~Expression() = default;

  // Attempt to do compile-time evaluation of the expression
  //  Throws an exception on error
  //  virtual ConstantValue evaluate() = 0;

  virtual void visit(ExpressionVisitor& visitor) = 0;

  virtual Expression* clone() const = 0;
};

/**
 * Comma-separated list of expressions
 */
class CommaExpression final: public Expression {

public:
  CommaExpression();
  ~CommaExpression();

  void add_expression(Expression* expr);

  const std::vector<Expression*>& get_expression_list() const;

private:
  std::vector<Expression*> expr_list;
};

/**
 * Expression that stores an assignment
 */
class AssignmentExpression final: public Expression {

public:
  AssignmentExpression(Expression* dest, Expression* src);

  Expression* get_source() const;
  Expression* get_destination() const;

private:
  Expression* dest;
  Expression* src;
};

/**
 * Casting from one data type to another
 */
class CastExpression final: public Expression {};

/**
 * Represents a string literal, like "Hello World!"
 */
class StringExpression final: public Expression {};

/**
 * Expression that represents a variable, like "i", "j", or "k"
 */
class IdentifierExpression final: public Expression {

public:
  IdentifierExpression(const std::string& identifier);

  // Get the stored identifier
  const std::string& get_identifier() const;

private:
  std::string identifier;
};

/**
 * Accessing element in an array or from a pointer
 */
class BracketExpression final: public Expression {

public:
  BracketExpression(Expression* expr, Expression* index);

  Expression* get_expression() const;
  Expression* get_index() const;

private:
  Expression* expr;
  Expression* index;
};

/**
 * Represents calling a function
 */
class FunctionCallExpression final: public Expression {

public:
  FunctionCallExpression(Expression* expr); // No arguments
  FunctionCallExpression(Expression* expr, const std::vector<Expression*>& parameters);

  Expression* get_expression() const;
  const std::vector<Expression*>& get_parameters_list() const;

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
  Expression* get_expression() const;

private:
  //  virtual ConstantValue unary_operator(ConstantValue value) = 0;

private:
  Expression* expr;
};

/**
 * Putting the minus symbol in front of a number
 */
class MinusExpression final: public UnaryExpression {

public:
  MinusExpression(Expression* expr);
};

/**
 * Boolean not (!)
 */
class NotExpression final: public UnaryExpression {

public:
  NotExpression(Expression* expr);
};

/**
 * Bitwise Complement (~)
 */
class ComplementExpression final: public UnaryExpression {

public:
  ComplementExpression(Expression* expr);
};

/**
 * Dereferencing a pointer
 */
class DereferenceExpression final: public UnaryExpression {

public:
  DereferenceExpression(Expression* expr);
};

/**
 * Get the address of a given variable
 */
class AddressOfExpression final: public UnaryExpression {

public:
  AddressOfExpression(Expression* expr);
};

/**
 * Get the size of a variable
 */
class SizeofExpression final: public UnaryExpression {

public:
  SizeofExpression(Expression* expr);
};

/**
 * Get the alignment of a variable
 */
class AlignofExpression final: public UnaryExpression {

public:
  AlignofExpression(Expression* expr);
};

/**
 * Bianry operators, like +, -, *, /, %, etc
 */
class BinaryExpression: public Expression {

public:
  BinaryExpression(Expression* left, Expression* right);
  ~BinaryExpression();

  Expression* get_left_expression() const;
  Expression* get_right_expression() const;

  //  ConstantValue evaluate();

private:
  // Compute a stored binary operator at runtime
  // virtual ConstantValue binary_operator(ConstantValue left, ConstantValue right) = 0;

private:
  Expression* left;
  Expression* right;
};

/**
 * Store an addition operator (+)
 */
class AdditionExpression final: public BinaryExpression {

public:
  AdditionExpression(Expression* left, Expression* right);
};

/**
 * Store a subtraction operator (-)
 */
class SubtractionExpression final: public BinaryExpression {

public:
  SubtractionExpression(Expression* left, Expression* right);
};

/**
 * Store a multiplication operator (*)
 */
class MultiplicationExpression final: public BinaryExpression {

public:
  MultiplicationExpression(Expression* left, Expression* right);
};

/**
 * Store a division operator (/)
 */
class DivisionExpression final: public BinaryExpression {

public:
  DivisionExpression(Expression* left, Expression* right);
};

/**
 * Store a modulus expression (%)
 */
class ModulusExpression final: public BinaryExpression {

public:
  ModulusExpression(Expression* left, Expression* right);
};

/**
 * Store a left bit shift expression (<<)
 */
class LeftShiftExpression final: public BinaryExpression {

public:
  LeftShiftExpression(Expression* left, Expression* right);
};

/**
 * Store a right bit shift expression
 */
class RightShiftExpression final: public BinaryExpression {

public:
  RightShiftExpression(Expression* left, Expression* right);
};

/**
 * Test for less than (<)
 */
class LessThanExpression final: public BinaryExpression {

public:
  LessThanExpression(Expression* left, Expression* right);
};

/**
 * Test for greater than (>)
 */
class GreaterThanExpression final: public BinaryExpression {

public:
  GreaterThanExpression(Expression* left, Expression* right);
};

/**
 * Test for less than or equal to (<=)
 */
class LessThanOrEqualExpression final: public BinaryExpression {

public:
  LessThanOrEqualExpression(Expression* left, Expression* right);
};

/**
 * Test for greater than or equal to (>=)
 */
class GreaterThanOrEqualExpression final: public BinaryExpression {

public:
  GreaterThanOrEqualExpression(Expression* left, Expression* right);
};

/**
 * Test for equality (==)
 */
class EqualsExpression final: public BinaryExpression {

public:
  EqualsExpression(Expression* left, Expression* right);
};

/**
 * Test for inequality (!=)
 */
class NotEqualsExpression final: public BinaryExpression {

public:
  NotEqualsExpression(Expression* left, Expression* right);
};

/**
 * Bitwise and (&)
 */
class BitwiseAndExpression final: public BinaryExpression {

public:
  BitwiseAndExpression(Expression* left, Expression* right);
};

/**
 * Bitwise or expression (|)
 */
class BitwiseOrExpression final: public BinaryExpression {

public:
  BitwiseOrExpression(Expression* left, Expression* right);
};

/**
 * Bitwise exclusive or (^)
 */
class BitwiseXorExpression final: public BinaryExpression {

public:
  BitwiseXorExpression(Expression* left, Expression* right);
};

/**
 * And expression used in an if statement (&&)
 */
class LogicalAndExpression final: public BinaryExpression {

public:
  LogicalAndExpression(Expression* left, Expression* right);
};

/**
 * Or logical expression used in an if statement (||)
 */
class LogicalOrExpression final: public BinaryExpression {

public:
  LogicalOrExpression(Expression* left, Expression* right);
};

/**
 * Stores expressions of the form (a ? b : c)
 */
class ConditionalExpression final: public Expression {

public:
  ConditionalExpression(Expression* condition, Expression* cond_true, Expression* cond_false);

  Expression* get_condition() const;
  Expression* get_true_expression() const;
  Expression* get_false_expression() const;

private:
  Expression* condition;
  Expression* cond_true;
  Expression* cond_false;
};

#endif /* Expression Header Included */