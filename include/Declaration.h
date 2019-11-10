#ifndef DECLARATION_HEADER
#define DECLARATION_HEADER

#include <string>
#include <vector>

// Forward declare classes
class DataType;
class DataTypeFactory;
class Expression;
class InitDeclarator;

typedef std::vector<InitDeclarator*> InitDeclList;

/**
 * @class AbstractDeclaration
 * Represents a data type with no name
 */
class AbstractDeclaration {

public:
  AbstractDeclaration(DataType* type);
  virtual ~AbstractDeclaration();

  DataType* get_type() const;
  virtual AbstractDeclaration* clone() const;

protected:
  DataType* type;
};

/**
 * @class Declaration
 * Represents a declaration with a variable name
 */
class Declaration final: public AbstractDeclaration {

public:
  Declaration(DataType* type, const std::string& name);
  Declaration(DataType* type, const std::string& name, Expression* initializer);

  const std::string& get_name() const;
  Declaration* clone() const;

private:
  std::string name;
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

  virtual AbstractDeclaration* build_declaration(DataType* internal_type) const;
  DataType* build_data_type(DataType* internal_type) const;

private:
  DataTypeFactory* sub_factory; // Can be NULL
};

/**
 * @class Declarator
 * Represents a declarator with a name
 */
class Declarator final: public AbstractDeclarator {

public:
  Declarator(const std::string& name);

  const std::string& get_name() const;

  Declaration* build_declaration(DataType* internal_type) const;

private:
  std::string name;
};

/**
 * @class InitDeclarator
 * Class that stores both a declarator and an initializer value
 */
class InitDeclarator final {

public:
  InitDeclarator(Declarator* decl);
  InitDeclarator(Declarator* decl, Expression* expr);
  ~InitDeclarator();

  Declarator* get_declarator() const;
  Expression* get_expression() const;

private:
  Declarator* decl;
  Expression* expr;
};

#endif /* Declaration Header Included */