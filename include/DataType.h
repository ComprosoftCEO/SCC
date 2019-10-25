#ifndef DATA_TYPE_HEADER
#define DATA_TYPE_HEADER

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

#endif /* Data Type Header Included */