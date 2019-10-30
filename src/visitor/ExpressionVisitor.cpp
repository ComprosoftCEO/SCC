#include <Expression.h>
#include <Visitor.h>

static inline void visit_unary_expression(UnaryExpression& expr, ExpressionVisitor& visitor) {
  expr.get_expression()->visit(visitor);
}

static inline void visit_binary_expression(BinaryExpression& expr, ExpressionVisitor& visitor) {
  expr.get_left_expression()->visit(visitor);
  expr.get_right_expression()->visit(visitor);
}

//
// Default implementations
//
void ExpressionVisitor::accept(CommaExpression& expr) {
  for (auto e: expr.get_expression_list()) { e->visit(*this); }
}

void ExpressionVisitor::accept(AssignmentExpression& expr) {
  expr.get_source()->visit(*this);
  expr.get_destination()->visit(*this);
}

void ExpressionVisitor::accept(CastExpression& expr) {
  expr.get_expression()->visit(*this);
}

void ExpressionVisitor::accept(StringExpression& expr) {}

void ExpressionVisitor::accept(IdentifierExpression& expr) {}

void ExpressionVisitor::accept(BracketExpression& expr) {
  expr.get_expression()->visit(*this);
  expr.get_index()->visit(*this);
}

void ExpressionVisitor::accept(FunctionCallExpression& expr) {
  expr.get_expression()->visit(*this);
  for (auto e: expr.get_parameters_list()) { e->visit(*this); }
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
  expr.get_condition()->visit(*this);
  expr.get_true_expression()->visit(*this);
  expr.get_false_expression()->visit(*this);
}
