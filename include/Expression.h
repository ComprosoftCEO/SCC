#ifndef EXPRESSION_HEADER
#define EXPRESSION_HEADER

#include <CTypes.h>
#include <OperatorEvaluator.h>
#include <string>
#include <vector>

// Forward declare classes
class ExpressionVisitor;
class DataType;
class ConstantExpression;

/**
 * @class Expression
 * Represents a generic expression in C
 */
class Expression {

public:
  virtual ~Expression() = default;

  // Attempt to do compile-time evaluation of the expression
  //  Returns nullptr on failure
  virtual ConstantExpression* evaluate() const;

  virtual void visit(ExpressionVisitor& visitor) = 0;
  virtual Expression* clone() const              = 0;

  // Does not visit if expr is null
  static void visit(Expression* expr, ExpressionVisitor& visitor);

  // Clone/evaluate or return a nullptr
  static Expression* clone(Expression* expr);
  static ConstantExpression* evaluate(Expression* expr);
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

  ConstantExpression* evaluate() const;
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

  ConstantExpression* evaluate() const;
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

  ConstantExpression* evaluate() const;
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

  // Convert the internal representation
  void convert_int();
  void convert_uint();
  void convert_long();
  void convert_ulong();
  void convert_longlong();
  void convert_ulonglong();
  void convert_float();
  void convert_double();
  void convert_longdouble();
  void convert_type(PrimitiveType type);

  // Test the "truthiness" of this value
  bool is_true() const;
  bool is_false() const;

  // Follow C integer casting rules
  static void upcast_values(ConstantExpression& one, ConstantExpression& two);

  ConstantExpression* evaluate() const;
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
 * @class UnaryExpression
 * Unary operators, like -, +, and !
 */
class UnaryExpression: public Expression {

public:
  UnaryExpression(Expression* expr);
  ~UnaryExpression();

  Expression* get_expression() const;

  ConstantExpression* evaluate() const final;

private:
  virtual const UnaryOperatorEvaluator& get_evaluator() const = 0;

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

private:
  const UnaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Boolean not (!)
 */
class NotExpression final: public UnaryExpression {

public:
  NotExpression(Expression* expr);

  void visit(ExpressionVisitor& visitor);
  NotExpression* clone() const;

private:
  const UnaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Bitwise Complement (~)
 */
class ComplementExpression final: public UnaryExpression {

public:
  ComplementExpression(Expression* expr);

  void visit(ExpressionVisitor& visitor);
  ComplementExpression* clone() const;

private:
  const UnaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Dereferencing a pointer
 */
class DereferenceExpression final: public Expression {

public:
  DereferenceExpression(Expression* expr);
  ~DereferenceExpression();

  Expression* get_expression() const;

  void visit(ExpressionVisitor& visitor);
  DereferenceExpression* clone() const;

private:
  Expression* expr;
};

/**
 * Get the address of a given variable
 */
class AddressOfExpression final: public Expression {

public:
  AddressOfExpression(Expression* expr);
  ~AddressOfExpression();

  Expression* get_expression() const;

  void visit(ExpressionVisitor& visitor);
  AddressOfExpression* clone() const;

private:
  Expression* expr;
};

/**
 * Get the size of a variable
 */
class SizeofExpression final: public Expression {

public:
  SizeofExpression(Expression* expr);
  SizeofExpression(DataType* dt);
  ~SizeofExpression();

  bool stores_expression() const;
  bool stores_data_type() const;
  Expression* get_expression() const;
  DataType* get_data_type() const;

  ConstantExpression* evaluate() const;

  void visit(ExpressionVisitor& visitor);
  SizeofExpression* clone() const;

private:
  bool is_data_type;
  Expression* expr;
  DataType* dt;
};

/**
 * Get the alignment of a variable
 */
class AlignofExpression final: public Expression {

public:
  AlignofExpression(DataType* dt);
  ~AlignofExpression();

  DataType* get_data_type() const;

  ConstantExpression* evaluate() const;

  void visit(ExpressionVisitor& visitor);
  AlignofExpression* clone() const;

private:
  DataType* dt;
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

  ConstantExpression* evaluate() const;

private:
  virtual const BinaryOperatorEvaluator& get_evaluator() const = 0;

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

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Store a subtraction operator (-)
 */
class SubtractionExpression final: public BinaryExpression {

public:
  SubtractionExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  SubtractionExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Store a multiplication operator (*)
 */
class MultiplicationExpression final: public BinaryExpression {

public:
  MultiplicationExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  MultiplicationExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Store a division operator (/)
 */
class DivisionExpression final: public BinaryExpression {

public:
  DivisionExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  DivisionExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Store a modulus expression (%)
 */
class ModulusExpression final: public BinaryExpression {

public:
  ModulusExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  ModulusExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Store a left bit shift expression (<<)
 */
class LeftShiftExpression final: public BinaryExpression {

public:
  LeftShiftExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  LeftShiftExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Store a right bit shift expression
 */
class RightShiftExpression final: public BinaryExpression {

public:
  RightShiftExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  RightShiftExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Test for less than (<)
 */
class LessThanExpression final: public BinaryExpression {

public:
  LessThanExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  LessThanExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Test for greater than (>)
 */
class GreaterThanExpression final: public BinaryExpression {

public:
  GreaterThanExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  GreaterThanExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Test for less than or equal to (<=)
 */
class LessThanOrEqualExpression final: public BinaryExpression {

public:
  LessThanOrEqualExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  LessThanOrEqualExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Test for greater than or equal to (>=)
 */
class GreaterThanOrEqualExpression final: public BinaryExpression {

public:
  GreaterThanOrEqualExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  GreaterThanOrEqualExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Test for equality (==)
 */
class EqualsExpression final: public BinaryExpression {

public:
  EqualsExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  EqualsExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Test for inequality (!=)
 */
class NotEqualsExpression final: public BinaryExpression {

public:
  NotEqualsExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  NotEqualsExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Bitwise and (&)
 */
class BitwiseAndExpression final: public BinaryExpression {

public:
  BitwiseAndExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  BitwiseAndExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Bitwise or expression (|)
 */
class BitwiseOrExpression final: public BinaryExpression {

public:
  BitwiseOrExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  BitwiseOrExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Bitwise exclusive or (^)
 */
class BitwiseXorExpression final: public BinaryExpression {

public:
  BitwiseXorExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  BitwiseXorExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * And expression used in an if statement (&&)
 */
class LogicalAndExpression final: public BinaryExpression {

public:
  LogicalAndExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  LogicalAndExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
};

/**
 * Or logical expression used in an if statement (||)
 */
class LogicalOrExpression final: public BinaryExpression {

public:
  LogicalOrExpression(Expression* left, Expression* right);

  void visit(ExpressionVisitor& visitor);
  LogicalOrExpression* clone() const;

private:
  const BinaryOperatorEvaluator& get_evaluator() const;
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

  ConstantExpression* evaluate() const;
  void visit(ExpressionVisitor& visitor);
  ConditionalExpression* clone() const;

private:
  Expression* condition;
  Expression* cond_true;
  Expression* cond_false;
};

#endif /* Expression Header Included */