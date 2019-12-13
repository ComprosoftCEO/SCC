#include <Expression.h>
#include <Visitor.h>

template<typename CAST, typename UNION>
static inline CAST cast_union(const UNION& u, PrimitiveType type) {
  // Ugly! Is there a better way to do this???
  // clang-format off
  switch (type) {
    case PrimitiveType::INT:        return (CAST) u.ival;
    case PrimitiveType::UINT:       return (CAST) u.uival;
    case PrimitiveType::LONG:       return (CAST) u.lval;
    case PrimitiveType::ULONG:      return (CAST) u.ulval;
    case PrimitiveType::LONGLONG:   return (CAST) u.llval;
    case PrimitiveType::ULONGLONG:  return (CAST) u.ullval;
    case PrimitiveType::FLOAT:      return (CAST) u.fval;
    case PrimitiveType::DOUBLE:     return (CAST) u.dval;
    case PrimitiveType::LONGDOUBLE: return (CAST) u.ldval;
    default:
      return (CAST) 0;
  }
  // clang-format on
}

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
// Casting
//
C_INT ConstantExpression::to_int() const {
  return cast_union<C_INT>(this->value, this->type);
}

C_UINT ConstantExpression::to_uint() const {
  return cast_union<C_UINT>(this->value, this->type);
}

C_LONG ConstantExpression::to_long() const {
  return cast_union<C_LONG>(this->value, this->type);
}

C_ULONG ConstantExpression::to_ulong() const {
  return cast_union<C_ULONG>(this->value, this->type);
}
C_LONGLONG ConstantExpression::to_longlong() const {
  return cast_union<C_LONGLONG>(this->value, this->type);
}

C_ULONGLONG ConstantExpression::to_ulonglong() const {
  return cast_union<C_ULONGLONG>(this->value, this->type);
}

C_FLOAT ConstantExpression::to_float() const {
  return cast_union<C_FLOAT>(this->value, this->type);
}

C_DOUBLE ConstantExpression::to_double() const {
  return cast_union<C_DOUBLE>(this->value, this->type);
}

C_LONGDOUBLE ConstantExpression::to_longdouble() const {
  return cast_union<C_LONGDOUBLE>(this->value, this->type);
}

//
// Convert internal representation
//
void ConstantExpression::convert_int() {
  this->value.ival = cast_union<C_INT>(this->value, this->type);
}

void ConstantExpression::convert_uint() {
  this->value.uival = cast_union<C_UINT>(this->value, this->type);
}

void ConstantExpression::convert_long() {
  this->value.lval = cast_union<C_LONG>(this->value, this->type);
}

void ConstantExpression::convert_ulong() {
  this->value.ulval = cast_union<C_ULONG>(this->value, this->type);
}

void ConstantExpression::convert_longlong() {
  this->value.llval = cast_union<C_LONGLONG>(this->value, this->type);
}

void ConstantExpression::convert_ulonglong() {
  this->value.ullval = cast_union<C_ULONGLONG>(this->value, this->type);
}

void ConstantExpression::convert_float() {
  this->value.fval = cast_union<C_FLOAT>(this->value, this->type);
}

void ConstantExpression::convert_double() {
  this->value.dval = cast_union<C_DOUBLE>(this->value, this->type);
}

void ConstantExpression::convert_longdouble() {
  this->value.ldval = cast_union<C_LONGDOUBLE>(this->value, this->type);
}

//
// Convert type from a parameter
//
void ConstantExpression::convert_type(PrimitiveType type) {
  // clang-format off
  switch (type) {
    case PrimitiveType::INT:        this->convert_int();
    case PrimitiveType::UINT:       this->convert_uint();
    case PrimitiveType::LONG:       this->convert_long();
    case PrimitiveType::ULONG:      this->convert_ulong();
    case PrimitiveType::LONGLONG:   this->convert_longlong();
    case PrimitiveType::ULONGLONG:  this->convert_ulonglong();
    case PrimitiveType::FLOAT:      this->convert_float();
    case PrimitiveType::DOUBLE:     this->convert_double();
    case PrimitiveType::LONGDOUBLE: this->convert_longdouble();
    default:
      return;
  }
  // clang-format on
}

//
// Get the "truthiness" of the expression
//
bool ConstantExpression::is_true() const {
  if (is_float_type(this->type)) { return true; }
  if (is_unsigned_type(this->type)) { return this->to_ulonglong() != 0; }
  return this->to_longlong() != 0;
}

bool ConstantExpression::is_false() const {
  return !this->is_true();
}

//
// Upcasting rules
//
void ConstantExpression::upcast_values(ConstantExpression& one, ConstantExpression& two) {
  PrimitiveType upcast = upcast_type(one.get_type(), two.get_type());
  one.convert_type(upcast);
  two.convert_type(upcast);
}

//
// Evaluate
//
ConstantExpression* ConstantExpression::evaluate() const {
  return this->clone();
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
