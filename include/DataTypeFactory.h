#ifndef DATA_TYPE_FACTORY_HEADER
#define DATA_TYPE_FACTORY_HEADER

#include <vector>

// Forward declare several classes
class DataType;
class Expression;
class Parameter;

typedef std::vector<Parameter*> ParameterList;

/**
 * @class DataTypeFactory
 * Factory that builds a data type object. The build_data_type() function
 *  should ONLY be called once, as resources might get moved by subtypes.
 */
class DataTypeFactory {

public:
  // Sub-factory can be a NULL pointer
  DataTypeFactory(DataTypeFactory* sub_factory);
  virtual ~DataTypeFactory();

  DataType* build_data_type(DataType* internal_type);

private:
  // Constructs the pointer, function, or array
  virtual DataType* build_aggregate(DataType* internal_type) = 0;

  DataTypeFactory* sub_factory;
};

/**
 * @class PointerFactory
 * Factory that build a pointer data type
 */
class PointerFactory final: public DataTypeFactory {

public:
  PointerFactory(DataTypeFactory* sub_factory);

private:
  DataType* build_aggregate(DataType* internal_type);
};

/**
 * @class ArrayFactory
 * Factory that build an array data type
 */
class ArrayFactory final: public DataTypeFactory {

public:
  ArrayFactory(DataTypeFactory* sub_factory);
  ArrayFactory(DataTypeFactory* sub_factory, Expression* size);

  ~ArrayFactory();

private:
  DataType* build_aggregate(DataType* internal_type);

  Expression* size;
};

/**
 * @class FunctionFactory
 * Factory that build a function data type
 */
class FunctionFactory final: public DataTypeFactory {

public:
  FunctionFactory(DataTypeFactory* sub_factory, const ParameterList& parameters);
  ~FunctionFactory();

private:
  DataType* build_aggregate(DataType* internal_type);

  ParameterList parameters;
};

/**
 * @class DataTypeFactoryFactory
 * Factory that builds data type factories
 */
class DataTypeFactoryFactory {

public:
  virtual ~DataTypeFactoryFactory() = default;

  virtual DataTypeFactory* build_factory(DataTypeFactory* parent) = 0;
};

/**
 * @class PointerFactoryFactory
 * Factory that builds pointer factories
 */
class PointerFactoryFactory final: public DataTypeFactory {

public:
  DataTypeFactory* build_factory(DataTypeFactory* parent);
};

/**
 * @class ArrayFactoryFactory
 * Factory that builds array factories
 */
class ArrayFactoryFactory final: public DataTypeFactoryFactory {

public:
  ArrayFactoryFactory();
  ArrayFactoryFactory(Expression* size);
  ~ArrayFactoryFactory();

  DataTypeFactory* build_factory(DataTypeFactory* parent);

private:
  Expression* size; // Ownership is moved to first object
  bool used;        // True if no longer has ownership of internal objects
};

/**
 * @class FunctionFactoryFactory
 * Factory that builds function factories
 */
class FunctionFactoryFactory final: public DataTypeFactoryFactory {

public:
  FunctionFactoryFactory(const ParameterList& parameters);
  ~FunctionFactoryFactory();

  DataTypeFactory* build_factory(DataTypeFactory* parent);

private:
  ParameterList parameters; // Ownership is moved to first object
  bool used;                // True if no longer has ownership of internal objects
};

#endif /* Data Type Factory Header Included */