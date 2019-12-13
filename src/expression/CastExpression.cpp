#include <DataType.h>
#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
CastExpression::CastExpression(Expression* expr, DataType* cast_to): expr(expr), cast_to(cast_to) {}

//
// Destructor
//
CastExpression::~CastExpression() {
  delete (this->expr);
  delete (this->cast_to);
}

//
// Getters
//
Expression* CastExpression::get_expression() {
  return this->expr;
}

DataType* CastExpression::get_cast_type() {
  return this->cast_to;
}

//
// Evaluate
//
ConstantExpression* CastExpression::evaluate() const {
  PrimitiveDataType* pdt = dynamic_cast<PrimitiveDataType*>(this->cast_to);
  if (pdt == nullptr) { return nullptr; }

  ConstantExpression* expr = Expression::evaluate(this->expr);
  if (expr == nullptr) { return nullptr; }

  // clang-format off
  switch(pdt->get_primitive_type()) {
    case PrimitiveType::INT:        expr->convert_int(); break;
    case PrimitiveType::UINT:       expr->convert_uint(); break;
    case PrimitiveType::LONG:       expr->convert_long(); break;
    case PrimitiveType::ULONG:      expr->convert_ulong(); break;
    case PrimitiveType::LONGLONG:   expr->convert_longlong(); break;
    case PrimitiveType::ULONGLONG:  expr->convert_ulonglong(); break;
    case PrimitiveType::FLOAT:      expr->convert_float(); break;
    case PrimitiveType::DOUBLE:     expr->convert_double(); break;
    case PrimitiveType::LONGDOUBLE: expr->convert_longdouble(); break;
    default:                        expr->convert_int(); break;
  }
  // clang-format on

  return expr;
}

//
// Clone
//
CastExpression* CastExpression::clone() const {
  return new CastExpression(this->expr->clone(), this->cast_to->clone());
}

//
// Visit
//
void CastExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}