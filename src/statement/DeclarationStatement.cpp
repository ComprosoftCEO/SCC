#include <Declaration.h>
#include <Statement.h>
#include <Visitor.h>

//
// Constructor
//
DeclarationStatement::DeclarationStatement(Declaration* decl): decl(decl) {}

//
// Destructor
//
DeclarationStatement::~DeclarationStatement() {
  delete (this->decl);
}

//
// Getters
//
Declaration* DeclarationStatement::get_declaration() const {
  return this->decl;
}

//
// Visit
//
void DeclarationStatement::visit(StatementVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
DeclarationStatement* DeclarationStatement::clone() const {
  return new DeclarationStatement(this->decl->clone());
}
