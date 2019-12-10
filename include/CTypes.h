#ifndef C_TYPES_HEADER
#define C_TYPES_HEADER

#include <cstddef> /* For size_t */
#include <cstdint>

// List of primitive types
enum class PrimitiveType {
  VOID,
  CHAR,
  UCHAR,
  SHORT,
  USHORT,
  INT,
  UINT,
  LONG,
  ULONG,
  LONGLONG,
  ULONGLONG,
  FLOAT,
  DOUBLE,
  LONGDOUBLE,
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
typedef __int128 C_LONGLONG;
typedef unsigned __int128 C_ULONGLONG;
typedef float C_FLOAT;
typedef double C_DOUBLE;
typedef long double C_LONGDOUBLE;

// List of all type specifiers
enum class TypeSpecifier {
  VOID,
  CHAR,
  SHORT,
  INT,
  LONG,
  FLOAT,
  DOUBLE,
  SIGNED,
  UNSIGNED,
  BOOL,
  COMPLEX,
  IMAGINARY,
};

// List of all type qualifiers
enum class TypeQualifier { CONST, RESTRICT, VOLATILE, ATOMIC };

// List of function specifiers
enum class FunctionSpecifier { INLINE, NORETURN };

// List of storage class specifiers
enum class StorageClassSpecifier { TYPEDEF, EXTERN, STATIC, THREAD_LOCAL, AUTO, REGISTER };

// List of custom sizes
#define POINTER_SIZE 8
#define VOID_SIZE    0

// Helper Functions
bool is_unsigned_type(PrimitiveType type);
bool is_integer_type(PrimitiveType type);
bool is_float_type(PrimitiveType type);

#endif /* C Types Header Included */