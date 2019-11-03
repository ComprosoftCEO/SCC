#ifndef DATA_TYPE_FACTORY_HEADER
#define DATA_TYPE_FACTORY_HEADER

#include <vector>

// Forward declare several classes
class DataType;
class Expression;
class Parameter;

typedef std::vector<Parameter> ParameterList;

/**
 * @class DataTypeFactory
 * Factory that builds a data type object. The build_data_type() function
 *  should ONLY be called once, as resources might get moved by subtypes.
 */
class DataTypeFactory {

  friend class AbstractDeclarator; // Hacky

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
  PointerFactory();
  PointerFactory(DataTypeFactory* sub_factory);

  void add_factory(DataTypeFactory* sub_factory);

private:
  DataType* build_aggregate(DataType* internal_type);
};

/**
 * @class ArrayFactory
 * Factory that build an array data type
 */
class ArrayFactory final: public DataTypeFactory {

public:
  ArrayFactory();
  ArrayFactory(Expression* size);

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
  FunctionFactory();
  FunctionFactory(const ParameterList& parameters, bool elipsis = false);

private:
  DataType* build_aggregate(DataType* internal_type);

  ParameterList parameters;
  bool elipsis;
};

#endif /* Data Type Factory Header Included */