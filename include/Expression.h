#ifndef EXPRESSION_HEADER
#define EXPRESSION_HEADER

#include <CTypes.h>
#include <ConstantValue.h>
#include <string>
#include <vector>

// Forward declare classes
class ExpressionVisitor;
class DataType;

class Expression {

public:
  virtual ~Expression() = default;

  // Attempt to do compile-time evaluation of the expression
  //  Throws an exception on error
  //  virtual ConstantValue evaluate() = 0;

  virtual void visit(ExpressionVisitor& visitor) = 0;

  virtual Expression* clone() const = 0;

  // Clone, or return a nullptr
  static Expression* clone(Expression* expr);
};

/**
 * Comma-separated list of expressions
 */
class CommaExpression final: public Expression {

public:
  CommaExpression();
  CommaExpression(const std::vector<Expression*>& expr_list);
  ~CommaExpression();

  void add_expression(Expression* expr);

  const std::vector<Expression*>& get_expression_list() const;

  void visit(ExpressionVisitor& visitor);
  CommaExpression* clone() const;

private:
  std::vector<Expression*> expr_list;
};

/**
 * Expression that stores an assignment
 */
class AssignmentExpression final: public Expression {

public:
  AssignmentExpression(Expression* dest, Expression* src);
  ~AssignmentExpression();

  Expression* get_source() const;
  Expression* get_destination() const;

  void visit(ExpressionVisitor& visitor);
  AssignmentExpression* clone() const;

private:
  Expression* dest;
  Expression* src;
};

/**
 * Casting from one data type to another
 */
class CastExpression final: public Expression {

public:
  CastExpression(Expression* expr, DataType* cast_to);
  ~CastExpression();

  Expression* get_expression();
  DataType* get_cast_type();

  void visit(ExpressionVisitor& visitor);
  CastExpression* clone() const;

private:
  Expression* expr;
  DataType* cast_to;
};

/**
 *@class ConstantExpression
 * Represents an expression that stores a literal
 */
class ConstantExpression final: public Expression {

public:
  explicit ConstantExpression(C_INT ival);
  explicit ConstantExpression(C_UINT uival);
  explicit ConstantExpression(C_LONG lval);
  explicit ConstantExpression(C_ULONG ulval);
  explicit ConstantExpression(C_LONGLONG llval);
  explicit ConstantExpression(C_ULONGLONG ullval);
  explicit ConstantExpression(C_FLOAT fval);
  explicit ConstantExpression(C_DOUBLE dval);
  explicit ConstantExpression(C_LONGDOUBLE ldval);

  PrimitiveType get_type() const;
  bool get_unsigned() const;

  // Casting types
  C_INT to_int() const;
  C_UINT to_uint() const;
  C_LONG to_long() const;
  C_ULONG to_ulong() const;
  C_LONGLONG to_longlong() const;
  C_ULONGLONG to_ulonglong() const;
  C_FLOAT to_float() const;
  C_DOUBLE to_double() const;
  C_LONGDOUBLE to_longdouble() const;

  void visit(ExpressionVisitor& visitor);
  ConstantExpression* clone() const;

private:
  union {
    C_INT ival;         // Integer
    C_UINT uival;       // Unsigned integer
    C_LONG lval;        // Long
    C_ULONG ulval;      // Unsigned long
    C_LONGLONG llval;   // Long long
    C_ULONGLONG ullval; // Unsigned long long
    C_FLOAT fval;       // Floating point
    C_DOUBLE dval;      // Double
    C_LONGDOUBLE ldval; // Long double
  } value;

  PrimitiveType type;
};

/**
 * Represents a string literal, like "Hello World!"
 */
class StringExpression final: public Expression {

public:
  StringExpression(const std::string& str);

  const std::string& get_string() const;

  void visit(ExpressionVisitor& visitor);
  StringExpression* clone() const;

private:
  std::string str;
};

/**
 * Expression that represents a variable, like "i", "j", or "k"
 */
class IdentifierExpression final: public Expression {

public:
  IdentifierExpression(const std::string& identifier);

  // Get the stored identifier
  const std::string& get_identifier() const;

  void visit(ExpressionVisitor& visitor);
  IdentifierExpression* clone() const;

private:
  std::string identifier;
};

/**
 * Accessing element in an array or from a pointer
 */
class BracketExpression final: public Expression {

public:
  BracketExpression(Expression* expr, Expression* index);
  ~BracketExpression();

  Expression* get_expression() const;
  Expression* get_index() const;

  void visit(ExpressionVisitor& visitor);
  BracketExpression* clone() const;

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
  ~FunctionCallExpression();

  Expression* get_expression() const;
  const std::vector<Expression*>& get_parameters_list() const;

  void visit(ExpressionVisitor& visitor);
  FunctionCallExpression* clone() const;

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
  ~UnaryExpression();

  // ConstantValue evaluate();
  Expression* get_expression() const;

private:
  //  virtual ConstantValue unary_operator(ConstantValue value) = 0;

protected:
  Expression* expr;
};

/**
 * Putting the minus symbol in front of a number
 */
class MinusExpression final: public UnaryExpression {

public:
  MinusExpression(Expression* expr);

  void visit(ExpressionVisitor& visitor);
  MinusExpression* clone() const;
};

/**
 * Boolean not (!)
 */
class NotExpression final: public UnaryExpression {

public:
  NotExpression(Expression* expr);

  void visit(ExpressionVisitor& visitor);
  NotExpression* clone() const;
};

/**
 * Bitwise Complement (~)
 */
class ComplementExpression final: public UnaryExpression {

public:
  ComplementExpression(Expression* expr);

  void visit(ExpressionVisitor& visitor);
  ComplementExpression* clone() const;
};

/**
 * Dereferencing a pointer
 */
class DereferenceExpression final: public UnaryExpression {

public:
  DereferenceExpression(Expression* expr);

  void visit(ExpressionVisitor& visitor);
  DereferenceExpression* clone() const;
};

/**
 * Get the address of a given variable
 */
class AddressOfExpression final: public UnaryExpression {

public:
  AddressOfExpression(Expression* expr);

  void visit(ExpressionVisitor& visitor);
  AddressOfExpression* clone() const;
};

/**
 * Get the size of a variable
 */
class SizeofExpression final: public UnaryExpression {

public:
  SizeofExpression(Expression* expr);

  void visit(ExpressionVisitor& visitor);
  SizeofExpression* clone() const;
};

/**
 * Get the alignment of a variable
 */
class AlignofExpression final: public UnaryExpression {

public:
  AlignofExpression(Expression* expr);

  void visit(ExpressionVisitor& visitor);
  AlignofExpression* clone() const;
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

protected:
  Expression* left;
  Expression* right;
};

/**
 * Store an addition operator (+)
 */
class AdditionExpression final: public BinaryExpression {

public:
  AdditionExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  AdditionExpression* clone() const;
};

/**
 * Store a subtraction operator (-)
 */
class SubtractionExpression final: public BinaryExpression {

public:
  SubtractionExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  SubtractionExpression* clone() const;
};

/**
 * Store a multiplication operator (*)
 */
class MultiplicationExpression final: public BinaryExpression {

public:
  MultiplicationExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  MultiplicationExpression* clone() const;
};

/**
 * Store a division operator (/)
 */
class DivisionExpression final: public BinaryExpression {

public:
  DivisionExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  DivisionExpression* clone() const;
};

/**
 * Store a modulus expression (%)
 */
class ModulusExpression final: public BinaryExpression {

public:
  ModulusExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  ModulusExpression* clone() const;
};

/**
 * Store a left bit shift expression (<<)
 */
class LeftShiftExpression final: public BinaryExpression {

public:
  LeftShiftExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  LeftShiftExpression* clone() const;
};

/**
 * Store a right bit shift expression
 */
class RightShiftExpression final: public BinaryExpression {

public:
  RightShiftExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  RightShiftExpression* clone() const;
};

/**
 * Test for less than (<)
 */
class LessThanExpression final: public BinaryExpression {

public:
  LessThanExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  LessThanExpression* clone() const;
};

/**
 * Test for greater than (>)
 */
class GreaterThanExpression final: public BinaryExpression {

public:
  GreaterThanExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  GreaterThanExpression* clone() const;
};

/**
 * Test for less than or equal to (<=)
 */
class LessThanOrEqualExpression final: public BinaryExpression {

public:
  LessThanOrEqualExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  LessThanOrEqualExpression* clone() const;
};

/**
 * Test for greater than or equal to (>=)
 */
class GreaterThanOrEqualExpression final: public BinaryExpression {

public:
  GreaterThanOrEqualExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  GreaterThanOrEqualExpression* clone() const;
};

/**
 * Test for equality (==)
 */
class EqualsExpression final: public BinaryExpression {

public:
  EqualsExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  EqualsExpression* clone() const;
};

/**
 * Test for inequality (!=)
 */
class NotEqualsExpression final: public BinaryExpression {

public:
  NotEqualsExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  NotEqualsExpression* clone() const;
};

/**
 * Bitwise and (&)
 */
class BitwiseAndExpression final: public BinaryExpression {

public:
  BitwiseAndExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  BitwiseAndExpression* clone() const;
};

/**
 * Bitwise or expression (|)
 */
class BitwiseOrExpression final: public BinaryExpression {

public:
  BitwiseOrExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  BitwiseOrExpression* clone() const;
};

/**
 * Bitwise exclusive or (^)
 */
class BitwiseXorExpression final: public BinaryExpression {

public:
  BitwiseXorExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  BitwiseXorExpression* clone() const;
};

/**
 * And expression used in an if statement (&&)
 */
class LogicalAndExpression final: public BinaryExpression {

public:
  LogicalAndExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  LogicalAndExpression* clone() const;
};

/**
 * Or logical expression used in an if statement (||)
 */
class LogicalOrExpression final: public BinaryExpression {

public:
  LogicalOrExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  LogicalOrExpression* clone() const;
};

/**
 * Stores expressions of the form (a ? b : c)
 */
class ConditionalExpression final: public Expression {

public:
  ConditionalExpression(Expression* condition, Expression* cond_true, Expression* cond_false);
  ~ConditionalExpression();

  Expression* get_condition() const;
  Expression* get_true_expression() const;
  Expression* get_false_expression() const;

  void visit(ExpressionVisitor& visitor);
  ConditionalExpression* clone() const;

private:
  Expression* condition;
  Expression* cond_true;
  Expression* cond_false;
};

#endif /* Expression Header Included */