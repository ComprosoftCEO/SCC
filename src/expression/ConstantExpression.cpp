#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
ConstantExpression::ConstantExpression(C_INT ival): value{.ival = ival}, type(PrimitiveType::INT) {}

ConstantExpression::ConstantExpression(C_UINT uival):
  value{.uival = uival}, type(PrimitiveType::UINT) {}

ConstantExpression::ConstantExpression(C_LONG lval):
  value{.lval = lval}, type(PrimitiveType::LONG) {}

ConstantExpression::ConstantExpression(C_ULONG ulval):
  value{.ulval = ulval}, type(PrimitiveType::ULONG) {}

ConstantExpression::ConstantExpression(C_LONGLONG llval):
  value{.llval = llval}, type(PrimitiveType::LONGLONG) {}

ConstantExpression::ConstantExpression(C_ULONGLONG ullval):
  value{.ullval = ullval}, type(PrimitiveType::ULONGLONG) {}

ConstantExpression::ConstantExpression(C_FLOAT fval):
  value{.fval = fval}, type(PrimitiveType::FLOAT) {}

ConstantExpression::ConstantExpression(C_DOUBLE dval):
  value{.dval = dval}, type(PrimitiveType::DOUBLE) {}

ConstantExpression::ConstantExpression(C_LONGDOUBLE ldval):
  value{.ldval = ldval}, type(PrimitiveType::LONGDOUBLE) {}

//
// Getters
//
PrimitiveType ConstantExpression::get_type() const {
  return this->type;
}

bool ConstantExpression::get_unsigned() const {
  return is_unsigned_type(this->type);
}

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
