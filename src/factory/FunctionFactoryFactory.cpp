#include <DataTypeFactory.h>

//
// Constructor
//
FunctionFactoryFactory::FunctionFactoryFactory(const ParameterList& parameters):
  parameters(parameters), used(false) {}

//
// Destructor
//
FunctionFactoryFactory::~FunctionFactoryFactory() {

  // Doesn't destruct if values moved
  if (this->used) { return; }
  for (auto param: this->parameters) { delete (param); }
}

//
// Build factory
//
DataTypeFactory* FunctionFactoryFactory::build_factory(DataTypeFactory* parent) {
  DataTypeFactory* new_factory = new FunctionFactory(parent, this->parameters);

  this->parameters.clear();
  this->used = true;

  return new_factory;
}
