#include <DataType.h>
#include <DataTypeFactory.h>

//
// Constructor
//
PointerFactory::PointerFactory(): DataTypeFactory(nullptr) {}

PointerFactory::PointerFactory(const std::vector<TypeQualifier>& qualifier_list):
  DataTypeFactory(nullptr), qualifier_list(qualifier_list) {}

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