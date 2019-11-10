#include <Declaration.h>
#include <Expression.h>

//
// Constructor
//
InitDeclarator::InitDeclarator(DataTypeFactory* sub_factory, const std::string& name,
                               Expression* expr):
  Declarator(sub_factory, name), expr(expr) {}

//
// Destructor
//
InitDeclarator::~InitDeclarator() {
  delete (this->expr);
}

//
// Getters
//
Expression* InitDeclarator::get_expression() const {
  return this->expr;
}

//
// Build the declaration
//
InitDeclaration* InitDeclarator::build_declaration(DataType* internal_type) const {
  return new InitDeclaration(this->build_data_type(internal_type), this->name,
                             Expression::clone(this->expr));
}
