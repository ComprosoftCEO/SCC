#include <DataTypeFactory.h>

//
// Constructor
//
ArrayFactoryFactory::ArrayFactoryFactory(): ArrayFactoryFactory(nullptr) {}

ArrayFactoryFactory::ArrayFactoryFactory(Expression* size): size(size), used(false) {}

//
// Destructor
//
ArrayFactoryFactory::~ArrayFactoryFactory() {
  // Don't destruct if value has been moved
  if (this->used) { return; }
  delete (this->size);
}

//
// Build the factory
//
DataTypeFactory* ArrayFactoryFactory::build_factory(DataTypeFactory* parent) {
  DataTypeFactory* new_factory = new ArrayFactory(parent, this->size);

  this->size = nullptr;
  this->used = true;

  return new_factory;
}
