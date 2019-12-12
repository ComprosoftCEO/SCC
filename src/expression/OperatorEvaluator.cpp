#include <Expression.h>
#include <OperatorEvaluator.h>

//
// Unary expression
//
ConstantExpression* UnaryOperatorEvaluator::evaluate(ConstantExpression* expr) const {
  if (expr == nullptr) { return nullptr; }

  // clang-format off
  switch (expr->get_type()) {
    case PrimitiveType::INT:        return this->do_operation(expr->to_int());
    case PrimitiveType::UINT:       return this->do_operation(expr->to_uint());
    case PrimitiveType::LONG:       return this->do_operation(expr->to_long());
    case PrimitiveType::ULONG:      return this->do_operation(expr->to_ulong());
    case PrimitiveType::LONGLONG:   return this->do_operation(expr->to_longlong());
    case PrimitiveType::ULONGLONG:  return this->do_operation(expr->to_ulonglong());
    case PrimitiveType::FLOAT:      return this->do_operation(expr->to_float());
    case PrimitiveType::DOUBLE:     return this->do_operation(expr->to_double());
    case PrimitiveType::LONGDOUBLE: return this->do_operation(expr->to_longdouble());
    default:
      return nullptr; // Should NOT happen
  }
  // clang-format on
}

//
// Binary expression
//
ConstantExpression* BinaryOperatorEvaluator::evaluate(ConstantExpression* left,

                                                      ConstantExpression* right) const {
  if (left == nullptr || right == nullptr) { return nullptr; }
  ConstantExpression::upcast_values(*left, *right);

  // clang-format off
  switch (left->get_type() /* Both should be same */) {
    case PrimitiveType::INT:        return this->do_operation(left->to_int(), right->to_int());
    case PrimitiveType::UINT:       return this->do_operation(left->to_uint(), right->to_uint());
    case PrimitiveType::LONG:       return this->do_operation(left->to_long(), right->to_long());
    case PrimitiveType::ULONG:      return this->do_operation(left->to_ulong(), right->to_ulong());
    case PrimitiveType::LONGLONG:   return this->do_operation(left->to_longlong(), right->to_longlong());
    case PrimitiveType::ULONGLONG:  return this->do_operation(left->to_ulonglong(), right->to_ulonglong());
    case PrimitiveType::FLOAT:      return this->do_operation(left->to_float(), right->to_float());
    case PrimitiveType::DOUBLE:     return this->do_operation(left->to_double(), right->to_double());
    case PrimitiveType::LONGDOUBLE: return this->do_operation(left->to_longdouble(), right->to_longdouble());
    default:
      return nullptr; // Should NOT happen
  }
  // clang-format on
}
