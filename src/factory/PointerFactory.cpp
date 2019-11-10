#include <DataType.h>
#include <DataTypeFactory.h>

//
// Constructor
//
PointerFactory::PointerFactory(): PointerFactory(nullptr) {}

PointerFactory::PointerFactory(DataTypeFactory* sub_factory): DataTypeFactory(sub_factory) {}

//
// Add the factory
//
void PointerFactory::add_factory(DataTypeFactory* sub_factory) {
  DataTypeFactory* sub = this;
  while (sub->get_sub_factory() != nullptr) { sub = sub->get_sub_factory(); }
  sub->set_sub_factory(sub_factory);
}

//
// Build the aggregate type
//
DataType* PointerFactory::build_aggregate(DataType* internal_type) {
  return new PointerDataType(internal_type);
}