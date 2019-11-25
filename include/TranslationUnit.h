#ifndef TRANSLATION_UNIT_HEADER
#define TRANSLATION_UNIT_HEADER

#include <Parameter.h>
#include <string>
#include <vector>

// Forward declare classes
class Declaration;
class Statement;
class FunctionDefinition;

typedef std::vector<FunctionDefinition*> FunctionDefinitionList;
typedef std::vector<Declaration*> DeclarationList;

/**
 * @class FuncitonDefinition
 * Defines a function in C
 */
class FunctionDefinition final {

public:
  FunctionDefinition(Declaration* decl, Statement* stmt);
  ~FunctionDefinition();

  bool is_valid_function() const;

  Declaration* get_declaration() const;
  Statement* get_statement() const;

  const std::string& get_name() const;
  const ParameterList& get_parameters() const;
  DataType* get_return_type() const;

private:
  Declaration* decl;
  Statement* stmt;
};

/**
 * @class TranslationUnit
 * Stores the list of function definitions and global variables
 */
class TranslationUnit final {

public:
  TranslationUnit();
  ~TranslationUnit();

  // Helper constructors
  TranslationUnit(FunctionDefinition* func_def);
  TranslationUnit(const DeclarationList& decl_list); // Takes ownership

  void add_function_definition(FunctionDefinition* func_def);
  void add_declarations(const DeclarationList& decl_list); // Takes ownership

private:
  // TODO: Store the order of declarations
  std::vector<FunctionDefinition*> functions;
  DeclarationList global_declarations;
};

#endif /* Translation Unit Header Included */
