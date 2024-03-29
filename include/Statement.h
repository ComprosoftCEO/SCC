#ifndef STATEMENT_HEADER
#define STATEMENT_HEADER

#include <string>
#include <vector>

class Statement;
class StatementVisitor;
class Expression;
class Declaration;

typedef std::vector<Statement*> StatementList;
typedef std::vector<Declaration*> DeclarationList;

/**
 * @class Statement
 * Represents a generic statement
 */
class Statement {

public:
  virtual ~Statement() = default;

  virtual void visit(StatementVisitor& visitor) = 0;
  virtual Statement* clone() const              = 0;

  // Does not visit if nullptr
  static void visit(Statement* stmt, StatementVisitor& visitor);

  // Clone method that clones or returns null
  static Statement* clone(Statement* stmt);
};

/**
 * @class EmptyStatement
 * Represents a statement that generates no code
 */
class EmptyStatement final: public Statement {

public:
  void visit(StatementVisitor& visitor);
  EmptyStatement* clone() const;
};

/**
 * @class DeclarationStatement
 * Statement that stores a declaration
 */
class DeclarationStatement final: public Statement {

public:
  DeclarationStatement(Declaration* decl);
  ~DeclarationStatement();

  Declaration* get_declaration() const;

  void visit(StatementVisitor& visitor);
  DeclarationStatement* clone() const;

private:
  Declaration* decl;
};

/**
 * @class LabelStatement
 * Represents a label. It's a proxy for its underlying statement type.
 */
class LabelStatement final: public Statement {

public:
  LabelStatement(const std::string& name, Statement* stmt);
  ~LabelStatement();

  const std::string& get_name() const;
  Statement* get_statement() const;

  void visit(StatementVisitor& visitor);
  LabelStatement* clone() const;

private:
  std::string name;
  Statement* stmt;
};

/**
 * @class CaseStatement
 * Represents a case for a switch statement
 */
class CaseStatement final: public Statement {

public:
  CaseStatement(Expression* value, Statement* stmt);
  ~CaseStatement();

  Expression* get_value() const;
  Statement* get_statement() const;

  void visit(StatementVisitor& visitor);
  CaseStatement* clone() const;

private:
  Expression* value;
  Statement* stmt;
};

/**
 * @class DefaultCaseStatement
 * Represents the default "case" label
 */
class DefaultCaseStatement final: public Statement {

public:
  DefaultCaseStatement(Statement* stmt);
  ~DefaultCaseStatement();

  Statement* get_statement() const;

  void visit(StatementVisitor& visitor);
  DefaultCaseStatement* clone() const;

private:
  Statement* stmt;
};

/**
 * @class CompoundStatement
 * Group of statements with a separate namespace
 */
class CompoundStatement final: public Statement {

public:
  CompoundStatement() = default;
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

  // Returns EmptyStatement() if expr is null
  static Statement* build_statement(Expression* expr);

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
 * @class SwitchStatement
 * Represents a switch/case block in C
 */
class SwitchStatement final: public Statement {

public:
  SwitchStatement(Expression* expr, Statement* stmt);
  ~SwitchStatement();

  Expression* get_expression() const;
  Statement* get_statement() const;

  void visit(StatementVisitor& visitor);
  SwitchStatement* clone() const;

private:
  Expression* expr;
  Statement* stmt;
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
  ForStatement(Statement* init, Expression* cond, Expression* loop, Statement* stmt);
  ForStatement(Expression* init, Expression* cond, Expression* loop, Statement* stmt);
  ForStatement(const DeclarationList& init, Expression* cond, Expression* loop, Statement* stmt);
  ~ForStatement();

  Statement* get_init_statement() const;
  Expression* get_cond_expression() const;
  Expression* get_loop_expression() const;
  Statement* get_statement() const;

  void visit(StatementVisitor& visitor);
  ForStatement* clone() const;

private:
  Statement* init;  // May be null
  Expression* cond; // May be null for infinite loop
  Expression* loop; // Expression to evaluate after each loop iteration
  Statement* stmt;  // Statement to execute inside the loop
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