#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
LogicalOrExpression::LogicalOrExpression(Expression* left, Expression* right):
  BinaryExpression(left, right) {}

//
// Clone
//
Expression* LogicalOrExpression::clone() const {
  return new LogicalOrExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void LogicalOrExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}