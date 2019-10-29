#include <DataTypeFactory.h>

//
// Build the factory
//
DataTypeFactory* PointerFactoryFactory::build_factory(DataTypeFactory* parent) {
  return new PointerFactory(parent);
}
