#include <DataType.h>
#include <DataTypeFactory.h>

//
// Constructor
//
FunctionFactory::FunctionFactory(DataTypeFactory* sub_factory, const ParameterList& parameters):
  DataTypeFactory(sub_factory), parameters(parameters) {}

//
// Destructor
//
FunctionFactory::~FunctionFactory() {
  for (auto param: this->parameters) { delete (param); }
}

//
// Build the aggregate type
//
DataType* FunctionFactory::build_aggregate(DataType* internal_type) {
  DataType* new_type = new FunctionDataType(this->parameters, internal_type);
  this->parameters.clear();
  return new_type;
}
