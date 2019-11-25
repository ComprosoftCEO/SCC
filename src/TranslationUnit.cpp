#include <Declaration.h>
#include <TranslationUnit.h>

//
// Constructor
//
TranslationUnit::TranslationUnit() = default;

TranslationUnit::TranslationUnit(FunctionDefinition* func_def): functions{func_def} {}

TranslationUnit::TranslationUnit(const DeclarationList& decl_list):
  global_declarations{decl_list} {}

//
// Destructor
//
TranslationUnit::~TranslationUnit() {
  for (auto func: this->functions) { delete (func); }
  for (auto decl: this->global_declarations) { delete (decl); }
}

//
// Add functions and declarations
//
void TranslationUnit::add_function_definition(FunctionDefinition* func_def) {
  this->functions.push_back(func_def);
}

void TranslationUnit::add_declarations(const DeclarationList& decl_list) {
  // Append to the end of the declarations
  this->global_declarations.insert(this->global_declarations.end(), decl_list.begin(),
                                   decl_list.end());
}
