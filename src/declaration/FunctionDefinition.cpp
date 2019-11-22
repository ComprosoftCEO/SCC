#include <DataType.h>
#include <Declaration.h>
#include <Statement.h>
#include <TranslationUnit.h>

//
// Constructor
//
FunctionDefinition::FunctionDefinition(Declaration* decl, Statement* stmt):
  decl(decl), stmt(stmt) {}

//
// Destructor
//
FunctionDefinition::~FunctionDefinition() {
  delete (this->decl);
  delete (this->stmt);
}

//
// Validate the function definition
//
bool FunctionDefinition::is_valid_function() const {
  FunctionDataType* fdt = dynamic_cast<FunctionDataType*>(this->decl->get_type());
  if (fdt == nullptr) { return false; }

  // TODO: Validate the return type

  return true;
}

//
// Getters
//
Declaration* FunctionDefinition::get_declaration() const {
  return this->decl;
}

Statement* FunctionDefinition::get_statement() const {
  return this->stmt;
}

const std::string& FunctionDefinition::get_name() const {
  return this->decl->get_name();
}

const ParameterList& FunctionDefinition::get_parameters() const {
  FunctionDataType* fdt = dynamic_cast<FunctionDataType*>(this->decl->get_type());
  if (fdt == nullptr) {
    static const ParameterList blank_list{};
    return blank_list;
  }
  return fdt->get_parameter_list();
}

DataType* FunctionDefinition::get_return_type() const {
  FunctionDataType* fdt = dynamic_cast<FunctionDataType*>(this->decl->get_type());
  if (fdt == nullptr) { return nullptr; }
  return fdt->get_return_type();
}
