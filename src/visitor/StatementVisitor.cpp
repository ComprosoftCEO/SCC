#include <Statement.h>
#include <Visitor.h>

void StatementVisitor::accept(EmptyStatement& stmt) {
  return;
}

void StatementVisitor::accept(LabelStatement& stmt) {
  Statement::visit(stmt.get_statement(), *this);
}

void StatementVisitor::accept(CaseStatement& stmt) {
  Statement::visit(stmt.get_statement(), *this);
}

void StatementVisitor::accept(DefaultCaseStatement& stmt) {
  Statement::visit(stmt.get_statement(), *this);
}

void StatementVisitor::accept(DeclarationStatement& stmt) {
  return;
}

void StatementVisitor::accept(CompoundStatement& stmt) {
  for (auto s: stmt.get_statement_list()) { Statement::visit(s, *this); }
}

void StatementVisitor::accept(ExpressionStatement& stmt) {
  return; // Override to have an expression visitor
}

void StatementVisitor::accept(IfStatement& stmt) {
  Statement::visit(stmt.get_then_statement(), *this);
  Statement::visit(stmt.get_else_statement(), *this);
}

void StatementVisitor::accept(SwitchStatement& stmt) {
  Statement::visit(stmt.get_statement(), *this);
}

void StatementVisitor::accept(GotoStatement& stmt) {
  return;
}

void StatementVisitor::accept(WhileStatement& stmt) {
  Statement::visit(stmt.get_statement(), *this);
}

void StatementVisitor::accept(DoWhileStatement& stmt) {
  Statement::visit(stmt.get_statement(), *this);
}

void StatementVisitor::accept(ForStatement& stmt) {
  Statement::visit(stmt.get_init_statement(), *this);
  Statement::visit(stmt.get_statement(), *this);
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
