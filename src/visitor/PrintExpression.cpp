#include <DataType.h>
#include <Expression.h>
#include <PrintVisitor.h>
#include <cstdio>

// Data type printer to use for all expressions
static PrintDataType PRINT_DATA_TYPE;

//
// Print a unary expression with parenthesis
//
static inline void print_unary(const char* symbol, UnaryExpression& expr,
                               ExpressionVisitor& visitor) {
  printf("(%s", symbol);
  Expression::visit(expr.get_expression(), visitor);
  printf(")");
}

//
// Print a binary expression with parenthesis
//
static inline void print_binary(const char* symbol, BinaryExpression& expr,
                                ExpressionVisitor& visitor) {
  printf("(");
  Expression::visit(expr.get_left_expression(), visitor);
  printf(" %s ", symbol);
  Expression::visit(expr.get_right_expression(), visitor);
  printf(")");
}

//
// Print a comma-separated list of expressions
//
void PrintExpression::accept(CommaExpression& expr) {
  printf("(");

  auto list = expr.get_expression_list();
  for (auto it = list.begin(); it != list.end(); ++it) {
    Expression::visit(*it, *this);
    if (it != std::prev(list.end())) { printf(", "); }
  }

  printf(")");
}

//
// Print a variable assignment
//
void PrintExpression::accept(AssignmentExpression& expr) {
  printf("(");
  Expression::visit(expr.get_destination(), *this);
  printf(" = ");
  Expression::visit(expr.get_source(), *this);
  printf(")");
}

//
// Print a cast expression
//
void PrintExpression::accept(CastExpression& expr) {
  printf("((");
  DataType::visit(expr.get_cast_type(), PRINT_DATA_TYPE);
  printf(") ");
  Expression::visit(expr.get_expression(), *this);
  printf(")");
}

//
// Print a constant expression
//
void PrintExpression::accept(ConstantExpression& expr) {
  switch (expr.get_type()) {
    case PrimitiveType::INT:
    case PrimitiveType::LONG:
    case PrimitiveType::LONGLONG:
      printf("%lld", (long long) expr.to_longlong());
      break;

    case PrimitiveType::UINT:
    case PrimitiveType::ULONG:
    case PrimitiveType::ULONGLONG:
      printf("%llu", (long long unsigned) expr.to_ulonglong());
      break;

    case PrimitiveType::FLOAT:
    case PrimitiveType::DOUBLE:
    case PrimitiveType::LONGDOUBLE:
      printf("%f", (double) expr.to_double());
  }
}

//
// Print a string literal
//
void PrintExpression::accept(StringExpression& expr) {
  // TODO: Print escape characters
  printf("(\"%s\")", expr.get_string().c_str());
}

//
// Print an identifier
//
void PrintExpression::accept(IdentifierExpression& expr) {
  printf("%s", expr.get_identifier().c_str());
}

//
// Print a bracket (array index) expression
//
void PrintExpression::accept(BracketExpression& expr) {
  printf("(");
  Expression::visit(expr.get_expression(), *this);
  printf("[");
  Expression::visit(expr.get_index(), *this);
  printf("])");
}

//
// Print a function call
//
void PrintExpression::accept(FunctionCallExpression& expr) {
  printf("(");
  Expression::visit(expr.get_expression(), *this);
  printf("(");

  auto list = expr.get_parameters_list();
  for (auto it = list.begin(); it != list.end(); ++it) {
    Expression* arg = *it;
    Expression::visit(arg, *this);
    if (it != std::prev(list.end())) { printf(", "); }
  }

  printf("))");
}

//
// Unary Expressions
//
void PrintExpression::accept(MinusExpression& expr) {
  print_unary("-", expr, *this);
}

void PrintExpression::accept(NotExpression& expr) {
  print_unary("!", expr, *this);
}

void PrintExpression::accept(ComplementExpression& expr) {
  print_unary("~", expr, *this);
}

void PrintExpression::accept(DereferenceExpression& expr) {
  printf("(*");
  Expression::visit(expr.get_expression(), *this);
  printf(")");
}

void PrintExpression::accept(AddressOfExpression& expr) {
  printf("(&");
  Expression::visit(expr.get_expression(), *this);
  printf(")");
}

void PrintExpression::accept(SizeofExpression& expr) {
  printf("(sizeof ");
  if (expr.stores_data_type()) {
    DataType::visit(expr.get_data_type(), PRINT_DATA_TYPE);
  } else {
    Expression::visit(expr.get_expression(), *this);
  }
  printf(")");
}

void PrintExpression::accept(AlignofExpression& expr) {
  printf("(alignof ");
  DataType::visit(expr.get_data_type(), PRINT_DATA_TYPE);
  printf(")");
}

//
// Binary Expressions
//
void PrintExpression::accept(AdditionExpression& expr) {
  print_binary("+", expr, *this);
}

void PrintExpression::accept(SubtractionExpression& expr) {
  print_binary("-", expr, *this);
}

void PrintExpression::accept(MultiplicationExpression& expr) {
  print_binary("*", expr, *this);
}

void PrintExpression::accept(DivisionExpression& expr) {
  print_binary("/", expr, *this);
}

void PrintExpression::accept(ModulusExpression& expr) {
  print_binary("%", expr, *this);
}

void PrintExpression::accept(LeftShiftExpression& expr) {
  print_binary("<<", expr, *this);
}

void PrintExpression::accept(RightShiftExpression& expr) {
  print_binary(">>", expr, *this);
}

void PrintExpression::accept(LessThanExpression& expr) {
  print_binary("<", expr, *this);
}

void PrintExpression::accept(GreaterThanExpression& expr) {
  print_binary(">", expr, *this);
}

void PrintExpression::accept(LessThanOrEqualExpression& expr) {
  print_binary("<=", expr, *this);
}

void PrintExpression::accept(GreaterThanOrEqualExpression& expr) {
  print_binary(">=", expr, *this);
}

void PrintExpression::accept(EqualsExpression& expr) {
  print_binary("==", expr, *this);
}

void PrintExpression::accept(NotEqualsExpression& expr) {
  print_binary("!=", expr, *this);
}

void PrintExpression::accept(BitwiseAndExpression& expr) {
  print_binary("&", expr, *this);
}

void PrintExpression::accept(BitwiseOrExpression& expr) {
  print_binary("|", expr, *this);
}

void PrintExpression::accept(BitwiseXorExpression& expr) {
  print_binary("^", expr, *this);
}
void PrintExpression::accept(LogicalAndExpression& expr) {
  print_binary("&&", expr, *this);
}

void PrintExpression::accept(LogicalOrExpression& expr) {
  print_binary("||", expr, *this);
}

//
// Three-way conditional
//
void PrintExpression::accept(ConditionalExpression& expr) {
  printf("(");
  Expression::visit(expr.get_condition(), *this);
  printf(" ? ");
  Expression::visit(expr.get_true_expression(), *this);
  printf(" : ");
  Expression::visit(expr.get_false_expression(), *this);
  printf(")");
}
