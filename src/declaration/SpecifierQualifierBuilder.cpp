#include "../parser/specifiers.tab.h"

#include <DataType.h>
#include <Declaration.h>
#include <map>

template<typename L1, typename L2> static inline void append_list(L1& list1, const L2& list2) {
  list1.insert(list1.end(), list2.begin(), list2.end());
}

//
// Constructors
//
SpecifierQualifierBuilder::SpecifierQualifierBuilder() = default;
SpecifierQualifierBuilder::SpecifierQualifierBuilder(const SpecifierQualifierBuilder& builder) =
    default;

// Type qualifiers
SpecifierQualifierBuilder::SpecifierQualifierBuilder(TypeQualifier qualifier):
  type_qualifiers{qualifier} {}

SpecifierQualifierBuilder::SpecifierQualifierBuilder(TypeQualifier qualifier,
                                                     const SpecifierQualifierBuilder& builder):
  SpecifierQualifierBuilder{builder} {
  this->type_qualifiers.push_front(qualifier);
}

// Storage class specifiers
SpecifierQualifierBuilder::SpecifierQualifierBuilder(StorageClassSpecifier specifier):
  storage_specifiers{specifier} {}

SpecifierQualifierBuilder::SpecifierQualifierBuilder(StorageClassSpecifier specifier,
                                                     const SpecifierQualifierBuilder& builder):
  SpecifierQualifierBuilder{builder} {
  this->storage_specifiers.push_front(specifier);
}

// Functions
SpecifierQualifierBuilder::SpecifierQualifierBuilder(FunctionSpecifier specifier):
  function_specifiers{specifier} {}

SpecifierQualifierBuilder::SpecifierQualifierBuilder(FunctionSpecifier specifier,
                                                     const SpecifierQualifierBuilder& builder):
  SpecifierQualifierBuilder{builder} {
  this->function_specifiers.push_front(specifier);
}

//
// Destructor
//
SpecifierQualifierBuilder::~SpecifierQualifierBuilder() {
  return;
}

//
// Merge the tokens
//
void SpecifierQualifierBuilder::merge_tokens(const SpecifierQualifierBuilder& builder) {
  append_list(this->type_specifiers, builder.type_specifiers);
  append_list(this->type_qualifiers, builder.type_qualifiers);
  append_list(this->storage_specifiers, builder.storage_specifiers);
  append_list(this->function_specifiers, builder.function_specifiers);
}

//
// Add type specifier tokens
//
void SpecifierQualifierBuilder::add_void() {
  this->type_specifiers.push_back(TypeSpecifier::VOID);
}

void SpecifierQualifierBuilder::add_char() {
  this->type_specifiers.push_back(TypeSpecifier::CHAR);
}

void SpecifierQualifierBuilder::add_short() {
  this->type_specifiers.push_back(TypeSpecifier::SHORT);
}

void SpecifierQualifierBuilder::add_int() {
  this->type_specifiers.push_back(TypeSpecifier::INT);
}

void SpecifierQualifierBuilder::add_long() {
  this->type_specifiers.push_back(TypeSpecifier::LONG);
}

void SpecifierQualifierBuilder::add_float() {
  this->type_specifiers.push_back(TypeSpecifier::FLOAT);
}

void SpecifierQualifierBuilder::add_double() {
  this->type_specifiers.push_back(TypeSpecifier::DOUBLE);
}

void SpecifierQualifierBuilder::add_signed() {
  this->type_specifiers.push_back(TypeSpecifier::SIGNED);
}

void SpecifierQualifierBuilder::add_unsigned() {
  this->type_specifiers.push_back(TypeSpecifier::UNSIGNED);
}

void SpecifierQualifierBuilder::add_bool() {
  this->type_specifiers.push_back(TypeSpecifier::BOOL);
}

//
// Qualifiers and specifiers
//
void SpecifierQualifierBuilder::add_type_qualifier(TypeQualifier qualifier) {
  this->type_qualifiers.push_back(qualifier);
}

void SpecifierQualifierBuilder::add_storage_class_specifier(StorageClassSpecifier specifier) {
  this->storage_specifiers.push_back(specifier);
}

void SpecifierQualifierBuilder::add_function_specifier(FunctionSpecifier specifier) {
  this->function_specifiers.push_back(specifier);
}

//
// Lexer used by the specifiers
//
int specifiers_lex(YYSTYPE* yylval, TypeSpecifierList& specifiers) {

  // Map of all token lookups
  static const std::map<TypeSpecifier, int> SPECIFIER_LOOKUP = {
      {TypeSpecifier::VOID, VOID},       {TypeSpecifier::CHAR, CHAR},
      {TypeSpecifier::SHORT, SHORT},     {TypeSpecifier::INT, INT},
      {TypeSpecifier::LONG, LONG},       {TypeSpecifier::FLOAT, SIGNED},
      {TypeSpecifier::DOUBLE, UNSIGNED}, {TypeSpecifier::SIGNED, FLOAT},
      {TypeSpecifier::UNSIGNED, DOUBLE}, {TypeSpecifier::BOOL, BOOL},
  };

  if (specifiers.empty()) { return EOF; }

  // Get the next specifier from the list
  TypeSpecifier next_specifier = specifiers.front();
  specifiers.pop_front();

  // Return the associated Bison token
  const auto lookup = SPECIFIER_LOOKUP.find(next_specifier);
  if (lookup != SPECIFIER_LOOKUP.end()) { return lookup->second; }

  return '?'; // Token to indicate invalid specifier
}
