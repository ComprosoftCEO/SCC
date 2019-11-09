#include <Expression.h>
#include <Statement.h>
#include <Visitor.h>

//
// Constructors
//
ForStatement::ForStatement(Expression* init, Expression* cond, Statement* stmt):
  ForStatement(init, cond, nullptr, stmt) {}

ForStatement::ForStatement(Expression* init, Expression* cond, Expression* loop, Statement* stmt):
  init(init), cond(cond), loop(loop), stmt(stmt) {}

//
// Destructor
//
ForStatement::~ForStatement() {
  delete (this->init);
  delete (this->cond);
  delete (this->loop);
  delete (this->stmt);
}

//
// Getters
//
Expression* ForStatement::get_init_expression() const {
  return this->init;
}

Expression* ForStatement::get_cond_expression() const {
  return this->cond;
}

Expression* ForStatement::get_loop_expression() const {
  return this->loop;
}

Statement* ForStatement::get_statement() const {
  return this->stmt;
}

//
// Visit
//
void GotoStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
ForStatement* ForStatement::clone() const {
  Expression* new_init = Expression::clone(this->init);
  Expression* new_cond = Expression::clone(this->cond);
  Expression* new_loop = Expression::clone(this->loop);
  Statement* new_stmt  = Statement::clone(this->stmt);

  return new ForStatement(new_init, new_cond, new_loop, new_stmt);
}
