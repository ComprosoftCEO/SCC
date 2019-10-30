#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
SubtractionExpression::SubtractionExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
Expression* SubtractionExpression::clone() const {
  return new SubtractionExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void SubtractionExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}