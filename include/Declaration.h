#ifndef DECLARATION_HEADER
#define DECLARATION_HEADER

#include <CTypes.h>
#include <list>
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
typedef std::list<TypeSpecifier> TypeSpecifierList;

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
  SpecifierQualifierBuilder(const SpecifierQualifierBuilder& builder);

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

  void merge_tokens(const SpecifierQualifierBuilder& builder);

  // Type specifier tokens
  void add_void();
  void add_char();
  void add_short();
  void add_int();
  void add_long();
  void add_float();
  void add_double();
  void add_signed();
  void add_unsigned();
  void add_bool();

  // TODO: Add structs or enums
  // TODO: Add typedef type

  // Qualifiers and specifiers
  void add_type_qualifier(TypeQualifier qualifier);
  void add_storage_class_specifier(StorageClassSpecifier specifier);
  void add_function_specifier(FunctionSpecifier specifier);

  // Builds a new clone of the internal data type
  //   Returns nullptr on failure
  DataType* get_data_type() const;

private:
  std::list<TypeSpecifier> type_specifiers;
  std::list<TypeQualifier> type_qualifiers;
  std::list<StorageClassSpecifier> storage_specifiers;
  std::list<FunctionSpecifier> function_specifiers;

  // TOOD: Complex data types
};

#endif /* Declaration Header Included */