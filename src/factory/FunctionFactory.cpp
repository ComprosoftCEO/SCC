#include <DataType.h>
#include <DataTypeFactory.h>

//
// Constructor
//
FunctionFactory::FunctionFactory(): DataTypeFactory(nullptr), elipsis(true) {}

FunctionFactory::FunctionFactory(const ParameterList& parameters, bool elipsis):
  DataTypeFactory(nullptr), parameters(parameters), elipsis(elipsis) {}

//
// Build the aggregate type
//
DataType* FunctionFactory::build_aggregate(DataType* internal_type) {
  DataType* new_type = new FunctionDataType(this->parameters, internal_type);
  return new_type;
}
