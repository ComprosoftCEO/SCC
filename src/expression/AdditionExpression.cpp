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
AdditionExpression* AdditionExpression::clone() const {
  return new AdditionExpression(this->left->clone(), this->right->clone());
}

//
// Visit
//
void AdditionExpression::visit(ExpressionVisitor& visitor) {
  visitor.accept(*this);
}

//
// Get binary operator
//
template<typename T> struct AdditionOperator {
  static ConstantExpression* evaluate(T left, T right) {
    return new ConstantExpression((T)(left + right));
  }
};

const BinaryOperatorEvaluator& AdditionExpression::get_evaluator() const {
  static const ConcreteBinaryOperatorEvaluator<AdditionOperator> evaluator;
  return evaluator;
}
