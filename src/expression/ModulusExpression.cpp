#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
ModulusExpression::ModulusExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
ModulusExpression* ModulusExpression::clone() const {
  return new ModulusExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void ModulusExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}