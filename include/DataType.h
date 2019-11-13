#ifndef DATA_TYPE_HEADER
#define DATA_TYPE_HEADER

#include <CTypes.h>
#include <Parameter.h>
#include <string>
#include <vector>

// List of all concrete data types
enum class ConcreteDataType { PRIMITIVE, POINTER, ARRAY, FUNCTION };

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
  static DataType* clone(DataType* type);

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
 * @class VoidDataType
 * Represents a "void" in C
 */
class VoidDataType final: public PrimitiveDataType {

public:
  VoidDataType();

  size_t size() const;
  VoidDataType* clone() const;
};

/**
 * @class CharDataType
 * Represents a 1-byte character data type
 */
class CharDataType final: public PrimitiveDataType {

public:
  CharDataType();

  size_t size() const;
  CharDataType* clone() const;
};

/**
 * @class IntDataType
 * Represents an integer (32 bit)
 */
class IntDataType final: public PrimitiveDataType {

public:
  IntDataType();

  size_t size() const;
  IntDataType* clone() const;
};

/**
 * @class LongDataType
 * Represents a long (32 or 64 bit integer)
 */
class LongDataType final: public PrimitiveDataType {

public:
  LongDataType();

  size_t size() const;
  LongDataType* clone() const;
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