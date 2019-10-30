#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
EqualsExpression::EqualsExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
EqualsExpression* EqualsExpression::clone() const {
  return new EqualsExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void EqualsExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}