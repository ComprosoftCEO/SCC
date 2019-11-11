#include <Expression.h>
#include <Statement.h>
#include <Visitor.h>

//
// Convert a declaration list into a block statement
//
static CompoundStatement* build_declaration_statement(const DeclarationList& list) {
  StatementList stmt_list;
  for (auto decl: list) { stmt_list.push_back(new DeclarationStatement(decl)); }
  return new CompoundStatement(stmt_list);
}

//
// Constructors
//
ForStatement::ForStatement(Statement* init, Expression* cond, Expression* loop, Statement* stmt):
  init(init), cond(cond), loop(loop), stmt(stmt) {}

ForStatement::ForStatement(Expression* init, Expression* cond, Expression* loop, Statement* stmt):
  ForStatement(ExpressionStatement::build_statement(init), cond, loop, stmt) {}

ForStatement::ForStatement(const DeclarationList& init, Expression* cond, Expression* loop,
                           Statement* stmt):
  ForStatement(build_declaration_statement(init), cond, loop, stmt) {}

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
Statement* ForStatement::get_init_statement() const {
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
void ForStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
ForStatement* ForStatement::clone() const {
  Statement* new_init  = Statement::clone(this->init);
  Expression* new_cond = Expression::clone(this->cond);
  Expression* new_loop = Expression::clone(this->loop);
  Statement* new_stmt  = Statement::clone(this->stmt);

  return new ForStatement(new_init, new_cond, new_loop, new_stmt);
}
