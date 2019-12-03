#include <DataType.h>
#include <DataTypeFactory.h>

//
// Constructor
//
FunctionFactory::FunctionFactory(): DataTypeFactory(), elipsis(true) {}

FunctionFactory::FunctionFactory(DataTypeFactory* sub_factory):
  DataTypeFactory(sub_factory), elipsis(true) {}

FunctionFactory::FunctionFactory(const ParameterList& parameters, bool elipsis):
  FunctionFactory(nullptr, parameters, elipsis) {}

FunctionFactory::FunctionFactory(DataTypeFactory* sub_factory, const ParameterList& parameters,
                                 bool elipsis):
  DataTypeFactory(sub_factory), parameters(parameters), elipsis(elipsis) {}

//
// Build the aggregate type
//
DataType* FunctionFactory::build_aggregate(DataType* internal_type) {
  return new FunctionDataType(this->parameters, internal_type);
}
