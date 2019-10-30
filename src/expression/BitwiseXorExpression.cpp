#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
BitwiseXorExpression::BitwiseXorExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
Expression* BitwiseXorExpression::clone() const {
  return new BitwiseXorExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void BitwiseXorExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}