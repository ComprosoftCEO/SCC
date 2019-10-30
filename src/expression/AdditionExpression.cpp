#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
AdditionExpression::AdditionExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
Expression* AdditionExpression::clone() const {
  return new AdditionExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void AdditionExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}