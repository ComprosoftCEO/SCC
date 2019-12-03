#include <CTypes.h>
#include <set>

// Set of unsigned types
static const std::set<PrimitiveType> unsigned_types = {
    PrimitiveType::UCHAR, PrimitiveType::USHORT,    PrimitiveType::UINT,
    PrimitiveType::ULONG, PrimitiveType::ULONGLONG,
};

// Set of integer types (signed or unsigned)
static const std::set<PrimitiveType> integer_types = {
    PrimitiveType::CHAR,     PrimitiveType::SHORT,     PrimitiveType::INT,    PrimitiveType::LONG,
    PrimitiveType::LONGLONG, PrimitiveType::UCHAR,     PrimitiveType::USHORT, PrimitiveType::UINT,
    PrimitiveType::ULONG,    PrimitiveType::ULONGLONG,

};

// Set of floating point types
static const std::set<PrimitiveType> float_types = {
    PrimitiveType::FLOAT,
    PrimitiveType::DOUBLE,
    PrimitiveType::LONGDOUBLE,
};

bool is_unsigned_type(PrimitiveType type) {
  return unsigned_types.find(type) != unsigned_types.end();
}

bool is_integer_type(PrimitiveType type) {
  return integer_types.find(type) != integer_types.end();
}

bool is_float_type(PrimitiveType type) {
  return float_types.find(type) != float_types.end();
}
