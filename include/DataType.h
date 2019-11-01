#ifndef DATA_TYPE_HEADER
#define DATA_TYPE_HEADER

#include <cstddef> /* For size_t */
#include <cstdint>
#include <string>
#include <vector>

// List of all concrete data types
enum class ConcreteDataType { PRIMITIVE, POINTER, ARRAY, FUNCTION };

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

// Typdef of literal sizes
typedef int8_t C_CHAR;
typedef uint8_t C_UCHAR;
typedef int16_t C_SHORT;
typedef uint16_t C_USHORT;
typedef int32_t C_INT;
typedef uint32_t C_UINT;
typedef int64_t C_LONG;
typedef uint64_t C_ULONG;
typedef C_LONG C_LONGLONG;
typedef C_ULONG C_ULONGLONG;
typedef float C_FLOAT;
typedef double C_DOUBLE;

// List of all type qualifiers
enum class TypeQualifier { CONST, RESTRICT, VOLATILE, ATOMIC };

// List of function specifiers
enum class FunctionSpecifier { INLINE, NORETURN };

// List of sizes
#define POINTER_SIZE 8

/**
 * @class DataType
 * Generic interface for working with any C type
 */
class DataType {

protected:
  DataType(ConcreteDataType concrete_type);

public:
  virtual ~DataType() = default;

  // Getter methods
  virtual size_t size() const = 0;
  ConcreteDataType get_concrete_type() const;

  virtual DataType* clone() const = 0;

private:
  // The underlying concrete type
  ConcreteDataType concrete_type;
};

/**
 * @class PrimitiveDataType
 * Represents a primitive data type (like int, float, etc.)
 */
class PrimitiveDataType: public DataType {

protected:
  PrimitiveDataType(PrimitiveType primitive_type);

public:
  PrimitiveType get_primitive_type() const;

private:
  PrimitiveType primitive_type;
};

/**
 * @class PointerDataType
 * Represents a pointer data type
 */
class PointerDataType final: public DataType {

public:
  PointerDataType(DataType* point_type);
  ~PointerDataType();

  DataType* get_point_type() const;
  size_t size() const;

  PointerDataType* clone() const;

private:
  DataType* point_type;
};

/**
 * @class ArrayDataType
 * Stores an Array definition
 */
class ArrayDataType final: public DataType {

public:
  ArrayDataType(DataType* type);
  ArrayDataType(DataType* type, class Expression* array_size);

  DataType* get_array_type() const;
  Expression* get_array_size() const;
  size_t size() const;

  DataType* clone() const;

private:
  DataType* type;
  class Expression* array_size;
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

  // Give parameters value semantics
  Parameter(const Parameter& other);
  Parameter(Parameter&& other);
  Parameter& operator=(const Parameter& other);
  Parameter& operator=(Parameter&& other);

  DataType* get_type() const;

  bool has_name() const;
  const std::string& get_name() const;

private:
  DataType* type;
  std::string name;
};

typedef std::vector<Parameter> ParameterList;

/**
 * @class FunctionDataType
 * Stores a function definition
 */
class FunctionDataType final: public DataType {

public:
  FunctionDataType(const ParameterList& parameters, DataType* return_type);
  ~FunctionDataType();

  DataType* get_return_type() const;
  const ParameterList& get_parameter_list() const;
  size_t size() const;

  DataType* clone() const;

private:
  ParameterList parameters;
  DataType* return_type;
};

#endif /* Data Type Header Included */