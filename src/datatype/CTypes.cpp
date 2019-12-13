#include <CTypes.h>
#include <map>
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

// Upcasting rules (each combination is only included once)
typedef std::pair<PrimitiveType, PrimitiveType> TypePair;
static const std::map<TypePair, PrimitiveType> upcast_rules = {
    {TypePair(PrimitiveType::CHAR, PrimitiveType::CHAR), PrimitiveType::INT},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::UCHAR), PrimitiveType::INT},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::SHORT), PrimitiveType::INT},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::USHORT), PrimitiveType::INT},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::INT), PrimitiveType::INT},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::UINT), PrimitiveType::UINT},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::LONG), PrimitiveType::LONG},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::ULONG), PrimitiveType::ULONG},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::LONGLONG), PrimitiveType::LONGLONG},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::ULONGLONG), PrimitiveType::ULONGLONG},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::FLOAT), PrimitiveType::FLOAT},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::CHAR, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::UCHAR), PrimitiveType::INT},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::SHORT), PrimitiveType::INT},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::USHORT), PrimitiveType::INT},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::INT), PrimitiveType::INT},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::UINT), PrimitiveType::UINT},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::LONG), PrimitiveType::LONG},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::ULONG), PrimitiveType::ULONG},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::LONGLONG), PrimitiveType::LONGLONG},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::ULONGLONG), PrimitiveType::ULONGLONG},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::FLOAT), PrimitiveType::FLOAT},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::UCHAR, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::SHORT, PrimitiveType::SHORT), PrimitiveType::INT},
    {TypePair(PrimitiveType::SHORT, PrimitiveType::USHORT), PrimitiveType::INT},
    {TypePair(PrimitiveType::SHORT, PrimitiveType::INT), PrimitiveType::INT},
    {TypePair(PrimitiveType::SHORT, PrimitiveType::UINT), PrimitiveType::UINT},
    {TypePair(PrimitiveType::SHORT, PrimitiveType::LONG), PrimitiveType::LONG},
    {TypePair(PrimitiveType::SHORT, PrimitiveType::ULONG), PrimitiveType::ULONG},
    {TypePair(PrimitiveType::SHORT, PrimitiveType::LONGLONG), PrimitiveType::LONGLONG},
    {TypePair(PrimitiveType::SHORT, PrimitiveType::ULONGLONG), PrimitiveType::ULONGLONG},
    {TypePair(PrimitiveType::SHORT, PrimitiveType::FLOAT), PrimitiveType::FLOAT},
    {TypePair(PrimitiveType::SHORT, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::SHORT, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::USHORT, PrimitiveType::USHORT), PrimitiveType::INT},
    {TypePair(PrimitiveType::USHORT, PrimitiveType::INT), PrimitiveType::INT},
    {TypePair(PrimitiveType::USHORT, PrimitiveType::UINT), PrimitiveType::UINT},
    {TypePair(PrimitiveType::USHORT, PrimitiveType::LONG), PrimitiveType::LONG},
    {TypePair(PrimitiveType::USHORT, PrimitiveType::ULONG), PrimitiveType::ULONG},
    {TypePair(PrimitiveType::USHORT, PrimitiveType::LONGLONG), PrimitiveType::LONGLONG},
    {TypePair(PrimitiveType::USHORT, PrimitiveType::ULONGLONG), PrimitiveType::ULONGLONG},
    {TypePair(PrimitiveType::USHORT, PrimitiveType::FLOAT), PrimitiveType::FLOAT},
    {TypePair(PrimitiveType::USHORT, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::USHORT, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::INT, PrimitiveType::INT), PrimitiveType::INT},
    {TypePair(PrimitiveType::INT, PrimitiveType::UINT), PrimitiveType::INT},
    {TypePair(PrimitiveType::INT, PrimitiveType::LONG), PrimitiveType::LONG},
    {TypePair(PrimitiveType::INT, PrimitiveType::ULONG), PrimitiveType::ULONG},
    {TypePair(PrimitiveType::INT, PrimitiveType::LONGLONG), PrimitiveType::LONGLONG},
    {TypePair(PrimitiveType::INT, PrimitiveType::ULONGLONG), PrimitiveType::ULONGLONG},
    {TypePair(PrimitiveType::INT, PrimitiveType::FLOAT), PrimitiveType::FLOAT},
    {TypePair(PrimitiveType::INT, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::INT, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::UINT, PrimitiveType::UINT), PrimitiveType::UINT},
    {TypePair(PrimitiveType::UINT, PrimitiveType::LONG), PrimitiveType::LONG},
    {TypePair(PrimitiveType::UINT, PrimitiveType::ULONG), PrimitiveType::ULONG},
    {TypePair(PrimitiveType::UINT, PrimitiveType::LONGLONG), PrimitiveType::LONGLONG},
    {TypePair(PrimitiveType::UINT, PrimitiveType::ULONGLONG), PrimitiveType::ULONGLONG},
    {TypePair(PrimitiveType::UINT, PrimitiveType::FLOAT), PrimitiveType::FLOAT},
    {TypePair(PrimitiveType::UINT, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::UINT, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::LONG, PrimitiveType::LONG), PrimitiveType::LONG},
    {TypePair(PrimitiveType::LONG, PrimitiveType::ULONG), PrimitiveType::LONG},
    {TypePair(PrimitiveType::LONG, PrimitiveType::LONGLONG), PrimitiveType::LONGLONG},
    {TypePair(PrimitiveType::LONG, PrimitiveType::ULONGLONG), PrimitiveType::ULONGLONG},
    {TypePair(PrimitiveType::LONG, PrimitiveType::FLOAT), PrimitiveType::FLOAT},
    {TypePair(PrimitiveType::LONG, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::LONG, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::ULONG, PrimitiveType::ULONG), PrimitiveType::ULONG},
    {TypePair(PrimitiveType::ULONG, PrimitiveType::LONGLONG), PrimitiveType::LONGLONG},
    {TypePair(PrimitiveType::ULONG, PrimitiveType::ULONGLONG), PrimitiveType::ULONGLONG},
    {TypePair(PrimitiveType::ULONG, PrimitiveType::FLOAT), PrimitiveType::FLOAT},
    {TypePair(PrimitiveType::ULONG, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::ULONG, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::LONGLONG, PrimitiveType::LONGLONG), PrimitiveType::LONGLONG},
    {TypePair(PrimitiveType::LONGLONG, PrimitiveType::ULONGLONG), PrimitiveType::LONGLONG},
    {TypePair(PrimitiveType::LONGLONG, PrimitiveType::FLOAT), PrimitiveType::FLOAT},
    {TypePair(PrimitiveType::LONGLONG, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::LONGLONG, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::ULONGLONG, PrimitiveType::ULONGLONG), PrimitiveType::ULONGLONG},
    {TypePair(PrimitiveType::ULONGLONG, PrimitiveType::FLOAT), PrimitiveType::FLOAT},
    {TypePair(PrimitiveType::ULONGLONG, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::ULONGLONG, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::FLOAT, PrimitiveType::FLOAT), PrimitiveType::FLOAT},
    {TypePair(PrimitiveType::FLOAT, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::FLOAT, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::DOUBLE, PrimitiveType::DOUBLE), PrimitiveType::DOUBLE},
    {TypePair(PrimitiveType::DOUBLE, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
    {TypePair(PrimitiveType::LONGDOUBLE, PrimitiveType::LONGDOUBLE), PrimitiveType::LONGDOUBLE},
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

//
// Upcasting rules
//

PrimitiveType upcast_type(PrimitiveType one, PrimitiveType two) {
  if (one == two) { return one; }
  if (one == PrimitiveType::VOID || two == PrimitiveType::VOID) {
    return PrimitiveType::VOID; /* Edge case */
  }

  // Search for the rule
  auto lookup = upcast_rules.find(TypePair(one, two));
  if (lookup == upcast_rules.end()) {
    // Try other combination
    lookup = upcast_rules.find(TypePair(two, one));
    if (lookup == upcast_rules.end()) { return one; /* Shouldn't happen */ }
  }

  return lookup->second;
}
