#ifndef FUNCTION_DEFINITION_HEADER
#define FUNCTION_DEFINITION_HEADER

#include <Parameter.h>
#include <string>
#include <vector>

// Forward declare classes
class Declaration;
class Statement;
class FunctionDefinition;

typedef std::vector<FunctionDefinition*> FunctionDefinitionList;

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

#endif /* Function Definition Header Included */
