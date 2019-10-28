#ifndef DATA_TYPE_HEADER
#define DATA_TYPE_HEADER

#include <cstddef> /* For size_t */

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
 * Generic Data Type
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
 * Represents a pointer data type
 */
class PointerDataType: public DataType {

public:
  PointerDataType(DataType* type);

  DataType* get_pointer_type() const;
  size_t size() const;
  size_t underlying_size() const;

private:
  DataType* type;
};

//
// Represents an array
//
class ArrayDataType: public DataType {

  ArrayDataType(DataType* type);
  ArrayDataType(DataType* type, size_t size);

  DataType* get_array_type() const;

private:
  DataType* type;
  size_t size;
};

#endif /* Data Type Header Included */