#ifndef ENUM_CONSTANT_HEADER
#define ENUM_CONSTANT_HEADER

#include <string>
#include <vector>

class Expression;

/**
 * @class EnumConstant
 * Associates an enum constant with a literal value
 */
class EnumConstant final {

public:
  EnumConstant(const std::string& name, Expression* value);
  ~EnumConstant();

  // Give it value semantics
  EnumConstant(const EnumConstant& other);
  EnumConstant& operator=(const EnumConstant& other);

  // Getters
  const std::string& get_name() const;
  const Expression* get_value() const;

  // Get the next sequenial value as a new expression
  Expression* get_next_value() const;

private:
  static void swap(EnumConstant& one, EnumConstant& two);

private:
  std::string name;
  Expression* value;
};

typedef std::vector<EnumConstant> EnumConstantList;

#endif