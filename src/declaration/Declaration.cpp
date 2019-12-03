#include <DataType.h>
#include <Declaration.h>
#include <Expression.h>
#include <PrintVisitor.h>
#include <cstdio>

//
// Constructor
//
Declaration::Declaration(DataType* type, const std::string& name):
  Declaration(type, name, nullptr) {}

Declaration::Declaration(DataType* type, const std::string& name, Expression* init):
  type(type), name(name), init(init) {}

//
// Destructor
//
Declaration::~Declaration() {
  delete (this->type);
  delete (this->init);
}

//
// Getters
//
DataType* Declaration::get_type() const {
  return this->type;
}

const std::string& Declaration::get_name() const {
  return this->name;
}

bool Declaration::has_initializer() const {
  return this->init != nullptr;
}

Expression* Declaration::get_initializer() const {
  return this->init;
}

//
// Print as a string to standard output
//
void Declaration::print() const {

  static PrintDataType PRINT_DATA_TYPE;
  static PrintExpression PRINT_EXPRESSION;

  DataType::visit(this->type, PRINT_DATA_TYPE);
  printf(" %s", this->name.c_str());

  if (this->has_initializer()) {
    printf(" = ");
    Expression::visit(this->get_initializer(), PRINT_EXPRESSION);
  }
}

//
// Clone
//
Declaration* Declaration::clone() const {
  return new Declaration(DataType::clone(this->type), this->name, Expression::clone(this->init));
}
