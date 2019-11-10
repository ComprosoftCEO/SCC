#ifndef DECLARATION_HEADER
#define DECLARATION_HEADER

#include <string>
#include <vector>

// Forward declare classes
class AbstractDeclaration;
class Declaration;
class InitDeclaration;
class AbstractDeclarator;
class Declarator;
class InitDeclarator;
class DataType;
class DataTypeFactory;
class Expression;
class InitDeclarator;

typedef std::vector<AbstractDeclaration*> AbsDeclList;
typedef std::vector<Declaration*> DeclList;
typedef std::vector<AbstractDeclarator*> AbsDeclrList;
typedef std::vector<Declarator*> DeclrList;

/**
 * @class AbstractDeclaration
 * Represents a data type with no name
 */
class AbstractDeclaration {

public:
  AbstractDeclaration(DataType* type);
  virtual ~AbstractDeclaration();

  DataType* get_type() const;

  virtual bool has_name() const; // If true, can cast to declaration
  Declaration* to_declaration();

  virtual AbstractDeclaration* clone() const;

protected:
  DataType* type;
};

/**
 * @class Declaration
 * Represents a declaration with a variable name
 */
class Declaration: public AbstractDeclaration {

public:
  Declaration(DataType* type, const std::string& name);

  bool has_name() const;
  const std::string& get_name() const;

  virtual bool has_initializer() const;
  InitDeclaration* to_init_declaration();

  Declaration* clone() const;

protected:
  std::string name;
};

/**
 * @class InitDeclaration
 * Represents a declaration that stores an initializer value
 */
class InitDeclaration final: public Declaration {

public:
  InitDeclaration(DataType* type, const std::string& name, Expression* init);
  ~InitDeclaration();

  bool has_initializer() const;
  Expression* get_initializer() const;

  InitDeclaration* clone() const;

private:
  Expression* init;
};

/**
 * @class AbstractDeclarator
 * Represents a declarator with no name
 */
class AbstractDeclarator {

public:
  AbstractDeclarator();
  AbstractDeclarator(DataTypeFactory* sub_factory);
  virtual ~AbstractDeclarator();

  void add_factory(DataTypeFactory* new_factory);

  DataType* build_data_type(DataType* internal_type) const;
  virtual AbstractDeclaration* build_declaration(DataType* internal_type) const;

protected:
  DataTypeFactory* sub_factory; // Can be NULL
};

/**
 * @class Declarator
 * Represents a declarator with a name
 */
class Declarator: public AbstractDeclarator {

public:
  Declarator(const std::string& name);
  Declarator(DataTypeFactory* sub_factory, const std::string& name);

  const std::string& get_name() const;

  Declaration* build_declaration(DataType* internal_type) const;

protected:
  std::string name;
};

/**
 * @class InitDeclarator
 * Class that stores both a declarator and an initializer value
 */
class InitDeclarator final: public Declarator {

public:
  InitDeclarator(DataTypeFactory* sub_factory, const std::string& name, Expression* expr);
  ~InitDeclarator();

  Expression* get_expression() const;

  InitDeclaration* build_declaration(DataType* internal_type) const;

private:
  Expression* expr;
};

#endif /* Declaration Header Included */