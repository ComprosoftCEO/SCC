#ifndef DECLARATOR_HEADER
#define DECLARATOR_HEADER

#include <string>

// Forward declare classes
class DataTypeFactory;
class DataTypeFactoryFactory;

/**
 * @class AbstractDeclarator
 * Represents a declarator with no name
 */
class AbstractDeclarator {

public:
  AbstractDeclarator();
  virtual ~AbstractDeclarator();

  void add_factory(const DataTypeFactoryFactory& build_factory);

  DataType* build_data_type(DataType* internal_type) const;

private:
  DataTypeFactory* factory; // Can be NULL
};

/**
 * @class Declarator
 * Represents a declarator with a name
 */
class Declarator final: public AbstractDeclarator {

public:
  Declarator(const std::string& name);

private:
  std::string name;
};

#endif /* Declarator Header Included */