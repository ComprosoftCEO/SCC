#ifndef STATEMENT_HEADER
#define STATEMENT_HEADER

#include <string>
#include <vector>

class Statement;
class StatementVisitor;
class Expression;

typedef std::vector<Statement*> StatementList;

/**
 * @class Statement
 * Represents a generic statement
 */
class Statement {

public:
  virtual ~Statement() = default;

  virtual void visit(StatementVisitor& visitor) = 0;
  virtual Statement* clone() const              = 0;
};

/**
 * @class LabelStatement
 * Represents a label
 */
class LabelStatement final: public Statement {

public:
  LabelStatement(const std::string& name);

  const std::string& get_name() const;

  void visit(StatementVisitor& visitor);
  LabelStatement* clone() const;

private:
  std::string name;
};

/**
 * @class CompoundStatement
 * Group of statements with a separate namespace
 */
class CompoundStatement final: public Statement {

public:
  CompoundStatement();
  CompoundStatement(const StatementList& stmt_list);
  ~CompoundStatement();

  const StatementList& get_statement_list() const;

  void visit(StatementVisitor& visitor);
  CompoundStatement* clone() const;

private:
  StatementList stmt_list;
};

/**
 * @class ExpressionStatement
 * Statement that represents an expression
 */
class ExpressionStatement final: public Statement {

public:
  ExpressionStatement(Expression* expr);
  ~ExpressionStatement();

  Expression* get_expression() const;

  void visit(StatementVisitor& visitor);
  ExpressionStatement* clone() const;

private:
  Expression* expr;
};

/**
 * @class IfStatement
 * Represents an "if" or an "if else" statement
 */
class IfStatement final: public Statement {

public:
  IfStatement(Expression* expr, Statement* then_stmt);
  IfStatement(Expression* expr, Statement* then_stmt, Statement* else_stmt);
  ~IfStatement();

  Expression* get_expression() const;
  Statement* get_then_statement() const;
  bool has_else_statement() const;
  Statement* get_else_statement() const; // May be NULL

  void visit(StatementVisitor& visitor);
  IfStatement* clone() const;

private:
  Expression* expr;
  Statement* then_stmt;
  Statement* else_stmt;
};

/**
 * @class GotoStatement
 * Goto a label
 */
class GotoStatement final: public Statement {

public:
  GotoStatement(const std::string& label);

  const std::string& get_label() const;

  void visit(StatementVisitor& visitor);
  GotoStatement* clone() const;

private:
  std::string label;
};

/**
 * @class WhileStatement
 * Stores a while loop in C
 */
class WhileStatement final: public Statement {

public:
  WhileStatement(Expression* expr, Statement* stmt);
  ~WhileStatement();

  Expression* get_expression() const;
  Statement* get_statement() const;

  void visit(StatementVisitor& visitor);
  WhileStatement* clone() const;

private:
  Expression* expr;
  Statement* stmt;
};

/**
 * @class DoWhileStatement
 * Stores a do-while loop in C
 */
class DoWhileStatement final: public Statement {

public:
  DoWhileStatement(Statement* stmt, Expression* expr);
  ~DoWhileStatement();

  Expression* get_expression() const;
  Statement* get_statement() const;

  void visit(StatementVisitor& visitor);
  DoWhileStatement* clone() const;

private:
  Expression* expr;
  Statement* stmt;
};

/**
 * @class ForStatement
 * Stores a for loop
 */
class ForStatement final: public Statement {

public:
};

/**
 * @class ContinueStatement
 * The "continue" keyword
 */
class ContinueStatement final: public Statement {

public:
  ContinueStatement() = default;

  void visit(StatementVisitor& visitor);
  ContinueStatement* clone() const;
};

/**
 * @class BreakStatement
 * The "break" keyword
 */
class BreakStatement final: public Statement {

public:
  BreakStatement() = default;

  void visit(StatementVisitor& visitor);
  BreakStatement* clone() const;
};

/**
 * @class ReturnStatement
 * Returning a value from a function
 */
class ReturnStatement final: public Statement {

public:
  ReturnStatement();
  ReturnStatement(Expression* expr);
  ~ReturnStatement();

  bool returns_value() const;
  Expression* get_return_expression() const;

  void visit(StatementVisitor& visitor);
  ReturnStatement* clone() const;

private:
  Expression* expr;
};

#endif /* Statement Header Included */