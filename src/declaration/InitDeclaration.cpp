#include <DataType.h>
#include <Declaration.h>
#include <Expression.h>

//
// Constructor
//
InitDeclaration::InitDeclaration(DataType* type, const std::string& name, Expression* init):
  Declaration(type, name), init(init) {}

//
// Destructor
//
InitDeclaration::~InitDeclaration() {
  delete (this->init);
}

//
// Getters
//
bool InitDeclaration::has_initializer() const {
  return true;
}

Expression* InitDeclaration::get_initializer() const {
  return this->init;
}

//
// Clone
//
InitDeclaration* InitDeclaration::clone() const {
  return new InitDeclaration(DataType::clone(this->type), this->name,
                             Expression::clone(this->init));
}
