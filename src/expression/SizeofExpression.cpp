#include <DataType.h>
#include <Expression.h>
#include <Visitor.h>

//
// Constructor.h
//
SizeofExpression::SizeofExpression(Expression* expr):
  is_data_type(false), expr(expr), dt(nullptr) {}

SizeofExpression::SizeofExpression(DataType* dt): is_data_type(true), expr(nullptr), dt(dt) {}

//
// Destructor
//
SizeofExpression::~SizeofExpression() {
  delete (this->expr);
  delete (this->dt);
}

//
// Getters
//
bool SizeofExpression::stores_expression() const {
  return !this->is_data_type;
}

bool SizeofExpression::stores_data_type() const {
  return this->is_data_type;
}

Expression* SizeofExpression::get_expression() const {
  return this->expr;
}

DataType* SizeofExpression::get_data_type() const {
  return this->dt;
}

//
// Evaluate
//
ConstantExpression* SizeofExpression::evaluate() const {
  if (this->is_data_type) {
    return (this->dt != nullptr) ? (new ConstantExpression((size_t) this->dt->size())) : nullptr;
  }
  return nullptr; // TODO: Get size of expression
}

//
// Clone
//
SizeofExpression* SizeofExpression::clone() const {
  if (this->is_data_type) { return new SizeofExpression(DataType::clone(this->dt)); }
  return new SizeofExpression(Expression::clone(this->expr));
}

//
// Visit
//
void SizeofExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}