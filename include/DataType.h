#ifndef DATA_TYPE_HEADER
#define DATA_TYPE_HEADER

#include <CTypes.h>
#include <Parameter.h>
#include <set>
#include <string>
#include <vector>

// List of all concrete data types
enum class ConcreteDataType { PRIMITIVE, POINTER, ARRAY, FUNCTION };

typedef std::set<FunctionSpecifier> FunctionSpecifierSet;
typedef std::set<TypeQualifier> TypeQualifierSet;

// Forward declare classes
class DataTypeVisitor;

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

  virtual DataType* clone() const              = 0;
  virtual void visit(DataTypeVisitor& visitor) = 0;

  // Does not visit if dt is null
  static void visit(DataType* dt, DataTypeVisitor& visitor);

  // Returns nullptr if type is null
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
  bool is_unsigned() const;

  static PrimitiveDataType* from_type(PrimitiveType type);

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
  void visit(DataTypeVisitor& visitor);
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
  void visit(DataTypeVisitor& visitor);
  CharDataType* clone() const;
};

/**
 * @class UnsignedCharDataType
 * Represents a 1-byte unsigned character data type
 */
class UnsignedCharDataType final: public PrimitiveDataType {

public:
  UnsignedCharDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  UnsignedCharDataType* clone() const;
};

/**
 * @class ShortDataType
 * Represents a 2-byte short data type
 */
class ShortDataType final: public PrimitiveDataType {

public:
  ShortDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  ShortDataType* clone() const;
};

/**
 * @class UnsignedShortDataType
 * Represents a 2-byte unsigned short data type
 */
class UnsignedShortDataType final: public PrimitiveDataType {

public:
  UnsignedShortDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  UnsignedShortDataType* clone() const;
};

/**
 * @class IntDataType
 * Represents an integer (32 bit)
 */
class IntDataType final: public PrimitiveDataType {

public:
  IntDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  IntDataType* clone() const;
};

/**
 * @class UnsignedIntDataType
 * Represents an unsigned 32-bit integer
 */
class UnsignedIntDataType final: public PrimitiveDataType {

public:
  UnsignedIntDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  UnsignedIntDataType* clone() const;
};

/**
 * @class LongDataType
 * Represents a long (64 bit integer)
 */
class LongDataType final: public PrimitiveDataType {

public:
  LongDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  LongDataType* clone() const;
};

/**
 * @class UnsignedLongDataType
 * Represents an unsigned long data type (64 bit integer)
 */
class UnsignedLongDataType final: public PrimitiveDataType {

public:
  UnsignedLongDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  UnsignedLongDataType* clone() const;
};

/**
 * @class LongLongDataType
 * Represents a long long (128-bit) integer
 */
class LongLongDataType final: public PrimitiveDataType {

public:
  LongLongDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  LongLongDataType* clone() const;
};

/**
 * @class UnsignedLongLongDataType
 * Represents an unsigned long long (128-bit) integer
 */
class UnsignedLongLongDataType final: public PrimitiveDataType {

public:
  UnsignedLongLongDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  UnsignedLongLongDataType* clone() const;
};

/**
 * @class FloatDataType
 * Represents a 32-bit floating point number
 */
class FloatDataType final: public PrimitiveDataType {

public:
  FloatDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  FloatDataType* clone() const;
};

/**
 * @class DoubleDataType
 * Represents a 64-bit floating point number
 */
class DoubleDataType final: public PrimitiveDataType {

public:
  DoubleDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  DoubleDataType* clone() const;
};

/**
 * @class LongDoubleDataType
 * Represents an 80-bit floating point number
 */
class LongDoubleDataType final: public PrimitiveDataType {

public:
  LongDoubleDataType();

  size_t size() const;
  void visit(DataTypeVisitor& visitor);
  LongDoubleDataType* clone() const;
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

  void visit(DataTypeVisitor& visitor);
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
  ~ArrayDataType();

  DataType* get_array_type() const;
  Expression* get_array_size() const;
  size_t size() const;

  void visit(DataTypeVisitor& visitor);
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
  void visit(DataTypeVisitor& visitor);
  DataType* clone() const;

private:
  ParameterList parameters;
  DataType* return_type;
};

#endif /* Data Type Header Included */