#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
LessThanExpression::LessThanExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
LessThanExpression* LessThanExpression::clone() const {
  return new LessThanExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void LessThanExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}