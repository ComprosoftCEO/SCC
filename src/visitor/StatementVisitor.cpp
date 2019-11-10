#include <Statement.h>
#include <Visitor.h>

void StatementVisitor::accept(EmptyStatement& stmt) {
  return;
}

void StatementVisitor::accept(LabelStatement& stmt) {
  return;
}

void StatementVisitor::accept(CompoundStatement& stmt) {
  for (auto s: stmt.get_statement_list()) {
    if (s != nullptr) { s->visit(*this); }
  }
}

void StatementVisitor::accept(ExpressionStatement& stmt) {
  return; // Override to have an expression visitor
}

void StatementVisitor::accept(IfStatement& stmt) {
  Statement *then_stmt = stmt.get_then_statement(), *else_stmt = stmt.get_else_statement();
  if (then_stmt != nullptr) { then_stmt->visit(*this); }
  if (else_stmt != nullptr) { else_stmt->visit(*this); }
}

void StatementVisitor::accept(GotoStatement& stmt) {
  return;
}

void StatementVisitor::accept(WhileStatement& stmt) {
  Statement* s = stmt.get_statement();
  if (s != nullptr) { s->visit(*this); }
}

void StatementVisitor::accept(DoWhileStatement& stmt) {
  Statement* s = stmt.get_statement();
  if (s != nullptr) { s->visit(*this); }
}

void StatementVisitor::accept(ForStatement& stmt) {
  return; // TODO: Implement this loop type
}

void StatementVisitor::accept(ContinueStatement& stmt) {
  return;
}

void StatementVisitor::accept(BreakStatement& stmt) {
  return;
}

void StatementVisitor::accept(ReturnStatement& stmt) {
  return;
}