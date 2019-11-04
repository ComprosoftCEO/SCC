#include <DataType.h>
#include <DataTypeFactory.h>

//
// Constructor
//
PointerFactory::PointerFactory(): PointerFactory(nullptr) {}

PointerFactory::PointerFactory(DataTypeFactory* sub_factory): DataTypeFactory(sub_factory) {}

//
// Build the aggregate type
//
DataType* PointerFactory::build_aggregate(DataType* internal_type) {
  return new PointerDataType(internal_type);
}
