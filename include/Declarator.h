#ifndef DECLARATOR_HEADER
#define DECLARATOR_HEADER

#include <functional>
#include <string>

// Forward declare classes
class DataTypeFactory;

typedef std::function<DataTypeFactory*(DataTypeFactory*)> DataTypeFactoryFactory;

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

#endif /* Declarator Header Included */