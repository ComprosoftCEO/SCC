#include <Expression.h>
#include <Visitor.h>

static inline void visit_unary_expression(UnaryExpression& expr, ExpressionVisitor& visitor) {
  Expression* e = expr.get_expression();
  if (e != nullptr) { e->visit(visitor); }
}

static inline void visit_binary_expression(BinaryExpression& expr, ExpressionVisitor& visitor) {
  Expression *left = expr.get_left_expression(), *right = expr.get_right_expression();
  if (left != nullptr) { left->visit(visitor); }
  if (right != nullptr) { right->visit(visitor); }
}

//
// Default implementations
//
void ExpressionVisitor::accept(CommaExpression& expr) {
  for (auto e: expr.get_expression_list()) {
    if (e != nullptr) { e->visit(*this); }
  }
}

void ExpressionVisitor::accept(AssignmentExpression& expr) {
  Expression *src = expr.get_source(), *dest = expr.get_destination();
  if (src != nullptr) { src->visit(*this); }
  if (dest != nullptr) { dest->visit(*this); }
}

void ExpressionVisitor::accept(CastExpression& expr) {
  Expression* cast = expr.get_expression();
  if (cast != nullptr) { cast->visit(*this); }
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
  Expression *e = expr.get_expression(), *index = expr.get_index();
  if (e != nullptr) { e->visit(*this); }
  if (index != nullptr) { index->visit(*this); }
}

void ExpressionVisitor::accept(FunctionCallExpression& expr) {
  Expression* func_expr = expr.get_expression();
  if (func_expr != nullptr) { func_expr->visit(*this); }

  for (auto e: expr.get_parameters_list()) {
    if (e != nullptr) { e->visit(*this); }
  }
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
  Expression* cond       = expr.get_condition();
  Expression* true_expr  = expr.get_true_expression();
  Expression* false_expr = expr.get_false_expression();

  if (cond != nullptr) { cond->visit(*this); }
  if (true_expr != nullptr) { true_expr->visit(*this); }
  if (false_expr != nullptr) { false_expr->visit(*this); }
}
