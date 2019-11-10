#ifndef DECLARATION_HEADER
#define DECLARATION_HEADER

#include <string>
#include <vector>

// Forward declare classes
class DataType;
class DataTypeFactory;
class Declaration;
class Declarator;
class PointerFactory;
class Expression;

typedef std::vector<Declarator*> DeclaratorList;
typedef std::vector<Declaration*> DeclarationList;

/**
 * @class Declaration
 * Represents a declaration with a variable name and possibly an initializer
 */
class Declaration final {

public:
  Declaration(DataType* type, const std::string& name);
  Declaration(DataType* type, const std::string& name, Expression* init);
  ~Declaration();

  DataType* get_type() const;
  const std::string& get_name() const;
  bool has_initializer() const;
  Expression* get_initializer() const;

  Declaration* clone() const;

protected:
  DataType* type;
  std::string name;
  Expression* init;
};

/**
 * @class Declarator
 * Represents a declarator with a name
 */
class Declarator final {

public:
  Declarator(const std::string& name);
  Declarator(DataTypeFactory* sub_factory, const std::string& name);
  ~Declarator();

  // Getters
  bool has_initializer() const;

  void add_factory(DataTypeFactory* new_factory);
  void add_factory(PointerFactory* pointer_factory);

  void set_initializer(Expression* init); // Replaces initializer in object

  Declaration* build_declaration(DataType* internal_type) const;

private:
  DataType* build_data_type(DataType* internal_type) const;

private:
  DataTypeFactory* sub_factory; // Can be NULL
  std::string name;
  Expression* init; // Initializer
};

#endif /* Declaration Header Included */