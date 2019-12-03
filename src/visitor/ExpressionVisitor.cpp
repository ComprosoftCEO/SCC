#include <Expression.h>
#include <Visitor.h>

static inline void visit_unary_expression(UnaryExpression& expr, ExpressionVisitor& visitor) {
  Expression::visit(expr.get_expression(), visitor);
}

static inline void visit_binary_expression(BinaryExpression& expr, ExpressionVisitor& visitor) {
  Expression::visit(expr.get_left_expression(), visitor);
  Expression::visit(expr.get_right_expression(), visitor);
}

//
// Default implementations
//
void ExpressionVisitor::accept(CommaExpression& expr) {
  for (auto e: expr.get_expression_list()) { Expression::visit(e, *this); }
}

void ExpressionVisitor::accept(AssignmentExpression& expr) {
  Expression::visit(expr.get_source(), *this);
  Expression::visit(expr.get_destination(), *this);
}

void ExpressionVisitor::accept(CastExpression& expr) {
  Expression::visit(expr.get_expression(), *this);
}

void ExpressionVisitor::accept(ConstantExpression& expr) {
  return;
}

void ExpressionVisitor::accept(StringExpression& expr) {
  return;
}

void ExpressionVisitor::accept(IdentifierExpression& expr) {
  return;
}

void ExpressionVisitor::accept(BracketExpression& expr) {
  Expression::visit(expr.get_expression(), *this);
  Expression::visit(expr.get_index(), *this);
}

void ExpressionVisitor::accept(FunctionCallExpression& expr) {
  Expression::visit(expr.get_expression(), *this);
  for (auto e: expr.get_parameters_list()) { Expression::visit(e, *this); }
}

void ExpressionVisitor::accept(MinusExpression& expr) {
  visit_unary_expression(expr, *this);
}

void ExpressionVisitor::accept(NotExpression& expr) {
  visit_unary_expression(expr, *this);
}

void ExpressionVisitor::accept(ComplementExpression& expr) {
  visit_unary_expression(expr, *this);
}

void ExpressionVisitor::accept(DereferenceExpression& expr) {
  visit_unary_expression(expr, *this);
}

void ExpressionVisitor::accept(AddressOfExpression& expr) {
  visit_unary_expression(expr, *this);
}

void ExpressionVisitor::accept(SizeofExpression& expr) {
  visit_unary_expression(expr, *this);
}

void ExpressionVisitor::accept(AlignofExpression& expr) {
  visit_unary_expression(expr, *this);
}

void ExpressionVisitor::accept(AdditionExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(SubtractionExpression& expr) {

  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(MultiplicationExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(DivisionExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(ModulusExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(LeftShiftExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(RightShiftExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(LessThanExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(GreaterThanExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(LessThanOrEqualExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(GreaterThanOrEqualExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(EqualsExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(NotEqualsExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(BitwiseAndExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(BitwiseOrExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(BitwiseXorExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(LogicalAndExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(LogicalOrExpression& expr) {
  visit_binary_expression(expr, *this);
}

void ExpressionVisitor::accept(ConditionalExpression& expr) {
  Expression::visit(expr.get_condition(), *this);
  Expression::visit(expr.get_true_expression(), *this);
  Expression::visit(expr.get_false_expression(), *this);
}
