#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
NotEqualsExpression::NotEqualsExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
NotEqualsExpression* NotEqualsExpression::clone() const {
  return new NotEqualsExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void NotEqualsExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}