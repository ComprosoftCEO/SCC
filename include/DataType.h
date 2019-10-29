#ifndef DATA_TYPE_HEADER
#define DATA_TYPE_HEADER

#include <cstddef> /* For size_t */
#include <string>
#include <vector>

// List of all concrete data types
enum class ConcreteDataType { PRIMITIVE, POINTER };

// List of primitive types
enum class PrimitiveType {
  CHAR,
  SHORT,
  INT,
  LONG,
  LONGLONG,
  FLOAT,
  DOUBLE,
};

// List of all type qualifiers
enum class TypeQualifier { CONST, RESTRICT, VOLATILE, ATOMIC };

// List of function specifiers
enum class FunctionSpecifier { INLINE, NORETURN };

/**
 * @class DataType
 * Generic interface for working with any C type
 */
class DataType {

protected:
  DataType(ConcreteDataType type);

  // Getter methods
  virtual size_t size() const = 0;
  ConcreteDataType get_data_type() const;

private:
  // The underlying concrete type
  ConcreteDataType type;
};

/**
 * @class PrimitiveDataType
 * Represents a primitive data type (like int, float, etc.)
 */
class PrimitiveDataType: public DataType {

public:
  PrimitiveDataType(PrimitiveType type);

  PrimitiveType get_primitive_type() const;
  size_t size() const;

private:
  PrimitiveType type;
};

/**
 * @class PointerDataType
 * Represents a pointer data type
 */
class PointerDataType final: public DataType {

public:
  PointerDataType(DataType* type);

  DataType* get_pointer_type() const;
  size_t size() const;
  size_t underlying_size() const;

private:
  DataType* type;
};

/**
 * @class ArrayDataType
 * Stores an Array definition
 */
class ArrayDataType final: public DataType {

  ArrayDataType(DataType* type);
  ArrayDataType(DataType* type, class Expression* size);

  DataType* get_array_type() const;

private:
  DataType* type;
  size_t size;
};

/**
 * @class Parameter
 * Stores a single parameter in a function
 */
class Parameter final {

public:
  Parameter(DataType* type);
  Parameter(DataType* type, const std::string& name);

  ~Parameter();

  DataType* get_type() const;

  bool has_name() const;
  const std::string& get_name() const;

private:
  DataType* type;
  std::string name;
};

typedef std::vector<Parameter*> ParameterList;

/**
 * @class FunctionDataType
 * Stores a function definition
 */
class FunctionDataType final: public DataType {

public:
  FunctionDataType(const ParameterList& parameters, DataType* return_type);

  DataType* get_return_type() const;
  const ParameterList& get_parameter_list() const;
  size_t size() const;

private:
  ParameterList parameters;
  DataType* return_type;
};

#endif /* Data Type Header Included */