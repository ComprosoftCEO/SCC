#include <Declaration.h>
#include <Expression.h>

//
// Constructor
//
InitDeclarator::InitDeclarator(Declarator* decl): InitDeclarator(decl, nullptr) {}

InitDeclarator::InitDeclarator(Declarator* decl, Expression* expr): decl(decl), expr(expr) {}

//
// Destructor
//
InitDeclarator::~InitDeclarator() {
  delete (this->decl);
  delete (this->expr);
}

//
// Getters
//
Declarator* InitDeclarator::get_declarator() const {
  return this->decl;
}

Expression* InitDeclarator::get_expression() const {
  return this->expr;
}
