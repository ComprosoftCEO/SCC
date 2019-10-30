#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
DivisionExpression::DivisionExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
DivisionExpression* DivisionExpression::clone() const {
  return new DivisionExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void DivisionExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}