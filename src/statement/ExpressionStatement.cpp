#include <Expression.h>
#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
ExpressionStatement::ExpressionStatement(Expression* expr): expr(expr) {}

//
// Destructor
//
ExpressionStatement::~ExpressionStatement() {
  delete (this->expr);
}

//
// Getters
//
Expression* ExpressionStatement::get_expression() const {
  return this->expr;
}

//
// Visit
//
void ExpressionStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
ExpressionStatement* ExpressionStatement::clone() const {
  return new ExpressionStatement(this->expr != nullptr ? this->expr->clone() : nullptr);
}
