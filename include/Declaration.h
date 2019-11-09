#ifndef DECLARATION_HEADER
#define DECLARATION_HEADER

#include <string>

// Forward declare classes
class DataType;
class DataTypeFactory;

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

private:
  std::string name;
};

#endif /* Declaration Header Included */