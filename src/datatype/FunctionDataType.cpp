#include <DataType.h>
#include <Visitor.h>

//
// Constructor
//
FunctionDataType::FunctionDataType(const ParameterList& parameters, DataType* return_type):
  DataType(ConcreteDataType::FUNCTION), parameters(parameters), return_type(return_type) {}

//
// Destructor
//
FunctionDataType::~FunctionDataType() {
  delete (this->return_type);
}

//
// Getters
//
DataType* FunctionDataType::get_return_type() const {
  return this->return_type;
}

const ParameterList& FunctionDataType::get_parameter_list() const {
  return this->parameters;
}

size_t FunctionDataType::size() const {
  return 0;
}

//
// Visit
//
void FunctionDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
DataType* FunctionDataType::clone() const {
  return new FunctionDataType(parameters, this->return_type->clone());
}
