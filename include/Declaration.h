#ifndef DECLARATION_HEADER
#define DECLARATION_HEADER

#include <CTypes.h>
#include <string>
#include <vector>

// Forward declare classes
class DataType;
class DataTypeFactory;
class Declaration;
class Declarator;
class PointerFactory;
class Expression;

typedef std::vector<Declarator*> DeclaratorList;
typedef std::vector<Declaration*> DeclarationList;

/**
 * @class Declaration
 * Represents a declaration with a variable name and possibly an initializer
 */
class Declaration final {

public:
  Declaration(DataType* type, const std::string& name);
  Declaration(DataType* type, const std::string& name, Expression* init);
  ~Declaration();

  DataType* get_type() const;
  const std::string& get_name() const;
  bool has_initializer() const;
  Expression* get_initializer() const;

  Declaration* clone() const;

protected:
  DataType* type;
  std::string name;
  Expression* init;
};

/**
 * @class Declarator
 * Represents a declarator with a name
 */
class Declarator final {

public:
  Declarator(const std::string& name);
  Declarator(DataTypeFactory* sub_factory, const std::string& name);
  ~Declarator();

  // Getters
  bool has_initializer() const;

  void add_factory(DataTypeFactory* new_factory);
  void add_factory(PointerFactory* pointer_factory);

  void set_initializer(Expression* init); // Replaces initializer in object

  Declaration* build_declaration(DataType* internal_type) const;

private:
  DataType* build_data_type(DataType* internal_type) const;

private:
  DataTypeFactory* sub_factory; // Can be NULL
  std::string name;
  Expression* init; // Initializer
};

enum class SpecifierQualifierState {
  START,              // No type yet
  PRIMITIVE,          // No signed or unsigned qualifier
  SIGNED_PRIMITIVE,   // Signed qualifier given
  UNSIGNED_PRIMITIVE, // Unsigned qualifier given
  COMPLEX_TYPE,       // Struct, union, or enum
};

/**
 * @class SpecifierQualifierBuilder
 * Nifty class for parsing the specifiers and qualifiers list
 */
class SpecifierQualifierBuilder final {

public:
  SpecifierQualifierBuilder();

  // Alternate Constructor helpers
  SpecifierQualifierBuilder(TypeQualifier qualifier);
  SpecifierQualifierBuilder(TypeQualifier qualifier, const SpecifierQualifierBuilder& builder);
  SpecifierQualifierBuilder(StorageClassSpecifier specifier);
  SpecifierQualifierBuilder(StorageClassSpecifier specifier,
                            const SpecifierQualifierBuilder& builder);
  SpecifierQualifierBuilder(FunctionSpecifier specifier);
  SpecifierQualifierBuilder(FunctionSpecifier specifier, const SpecifierQualifierBuilder& builder);

  // Destructor
  ~SpecifierQualifierBuilder();

  bool merge_tokens(const SpecifierQualifierBuilder& builder);

  // Type specifier tokens
  bool add_void();
  bool add_char();
  bool add_short();
  bool add_int();
  bool add_long();
  bool add_float();
  bool add_double();
  bool add_signed();
  bool add_unsigned();
  bool add_bool();

  // TODO: Add structs or enums
  // TODO: Add typedef type

  // Qualifiers and specifiers
  bool add_type_qualifier(TypeQualifier qualifier);
  bool add_storage_class_specifier(StorageClassSpecifier specifier);
  bool add_function_specifier(FunctionSpecifier specifier);

  // Builds a new clone of the internal data type
  DataType* get_data_type() const;

private:
  bool inside_complex_state() const;

private:
  SpecifierQualifierState state; // Current state
  union {
    PrimitiveType primitive_type; // Current type
    DataType* complex_type;       // For struct or union types
  };
};

#endif /* Declaration Header Included */