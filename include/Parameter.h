#ifndef PARAMETER_HEADER
#define PARAMETER_HEADER

#include <string>
#include <vector>

// Forward declare classes
class DataType;
class Declaration;

/**
 * @class Parameter
 * Stores a single parameter in a function
 */
class Parameter final {

public:
  Parameter(DataType* type);
  Parameter(DataType* type, const std::string& name);
  Parameter(Declaration* decl); // Deletes the declaration
  ~Parameter();

  // Give parameters value semantics
  Parameter(const Parameter& other);
  Parameter& operator=(const Parameter& other);

  DataType* get_type() const;

  bool has_name() const;
  const std::string& get_name() const;

private:
  static void swap(Parameter& one, Parameter& two);

private:
  DataType* type;
  std::string name;
};

typedef std::vector<Parameter> ParameterList;

#endif /* Parameter Header Included */