#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
AssignmentExpression::AssignmentExpression(Expression* dest, Expression* src):
  dest(dest), src(src) {}

//
// Destructor
//
AssignmentExpression::~AssignmentExpression() {
  delete (this->dest);
  delete (this->src);
}

//
// Getters
//
Expression* AssignmentExpression::get_source() const {
  return this->src;
}

Expression* AssignmentExpression::get_destination() const {
  return this->dest;
}

//
// Evaluate
//
ConstantExpression* AssignmentExpression::evaluate() const {
  return Expression::evaluate(this->src);
}

//
// Clone
//
AssignmentExpression* AssignmentExpression::clone() const {
  return new AssignmentExpression(this->dest->clone(), this->src->clone());
}

//
// Visit
//
void AssignmentExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}
