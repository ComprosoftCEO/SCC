#include <DataType.h>
#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
AlignofExpression::AlignofExpression(DataType* dt): dt(dt) {}

//
// Destructor
//
AlignofExpression::~AlignofExpression() {
  delete (this->dt);
}

//
// Getters
//
DataType* AlignofExpression::get_data_type() const {
  return this->dt;
}

//
// Evaluate
//
ConstantExpression* AlignofExpression::evaluate() const {
  if (this->dt == nullptr) { return nullptr; }
  return new ConstantExpression((size_t) this->dt->size());
}

//
// Clone
//
AlignofExpression* AlignofExpression::clone() const {
  return new AlignofExpression(DataType::clone(this->dt));
}

//
// Visit
//
void AlignofExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}