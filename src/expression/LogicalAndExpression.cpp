#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
LogicalAndExpression::LogicalAndExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
LogicalAndExpression* LogicalAndExpression::clone() const {
  return new LogicalAndExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void LogicalAndExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}