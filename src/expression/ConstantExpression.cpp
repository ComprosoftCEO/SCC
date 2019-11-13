#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
ConstantExpression::ConstantExpression(C_INT ival):
  value{.ival = ival}, type(PrimitiveType::INT), is_unsigned(false) {}

ConstantExpression::ConstantExpression(C_UINT uival):
  value{.uival = uival}, type(PrimitiveType::INT), is_unsigned(true) {}

ConstantExpression::ConstantExpression(C_LONG lval):
  value{.lval = lval}, type(PrimitiveType::LONG), is_unsigned(false) {}

ConstantExpression::ConstantExpression(C_ULONG ulval):
  value{.ulval = ulval}, type(PrimitiveType::LONG), is_unsigned(true) {}

ConstantExpression::ConstantExpression(C_LONGLONG llval):
  value{.llval = llval}, type(PrimitiveType::LONGLONG), is_unsigned(false) {}

ConstantExpression::ConstantExpression(C_ULONGLONG ullval):
  value{.ullval = ullval}, type(PrimitiveType::LONGLONG), is_unsigned(true) {}

ConstantExpression::ConstantExpression(C_FLOAT fval):
  value{.fval = fval}, type(PrimitiveType::FLOAT), is_unsigned(false) {}

ConstantExpression::ConstantExpression(C_DOUBLE dval):
  value{.dval = dval}, type(PrimitiveType::DOUBLE), is_unsigned(false) {}

ConstantExpression::ConstantExpression(C_LONGDOUBLE ldval):
  value{.ldval = ldval}, type(PrimitiveType::LONGDOUBLE), is_unsigned(false) {}

//
// Visit
//
void ConstantExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
ConstantExpression* ConstantExpression::clone() const {
  // Copy semantics should work fine, no pointers to copy
  return new ConstantExpression(*this);
}
