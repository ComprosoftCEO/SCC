#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
GreaterThanExpression::GreaterThanExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
Expression* GreaterThanExpression::clone() const {
  return new GreaterThanExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void GreaterThanExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}