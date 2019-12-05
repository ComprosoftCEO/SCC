#include <DataType.h>
#include <Declaration.h>
#include <Expression.h>
#include <PrintVisitor.h>
#include <Statement.h>
#include <TranslationUnit.h>
#include <cstdio>

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

//
// Print everything to standard output
//
void TranslationUnit::print_code() const {

  // Stateless classes
  static PrintExpression PRINT_EXPRESSION;
  static PrintDataType PRINT_DATA_TYPE;
  PrintStatement PRINT_STATEMENT;

  // First print global variables
  for (auto decl: this->global_declarations) {
    if (decl == nullptr) { continue; }
    decl->print();
    printf(";\n");
  }

  if (this->global_declarations.size() > 0) { printf("\n"); }

  // Next print the functions, one at a time
  for (auto def: this->functions) {
    if (def == nullptr) { continue; }

    def->get_declaration()->print();
    printf(" {\n");
    PRINT_STATEMENT.visitIgnoreBrackets(def->get_statement());
    printf("}\n\n");
  }
}
