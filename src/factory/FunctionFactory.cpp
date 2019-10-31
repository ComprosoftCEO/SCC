#include <DataType.h>
#include <DataTypeFactory.h>

//
// Constructor
//
FunctionFactory::FunctionFactory(DataTypeFactory* sub_factory, const ParameterList& parameters):
  DataTypeFactory(sub_factory), parameters(parameters) {}

//
// Build the aggregate type
//
DataType* FunctionFactory::build_aggregate(DataType* internal_type) {
  DataType* new_type = new FunctionDataType(this->parameters, internal_type);
  return new_type;
}
