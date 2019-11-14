#include <CTypes.h>
#include <set>

// Set of unsigned types
static const std::set<PrimitiveType> unsigned_types = {
    PrimitiveType::UCHAR, PrimitiveType::USHORT,    PrimitiveType::UINT,
    PrimitiveType::ULONG, PrimitiveType::ULONGLONG,
};

bool is_unsigned_type(PrimitiveType type) {
  return unsigned_types.find(type) != unsigned_types.end();
}
