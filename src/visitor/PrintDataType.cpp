#include <DataType.h>
#include <Expression.h>
#include <PrintVisitor.h>
#include <cstdio>

//
// Visit all of the primitive types
//
void PrintDataType::accept(VoidDataType& dt) {
  printf("void");
}

void PrintDataType::accept(CharDataType& dt) {
  printf("char");
}

void PrintDataType::accept(UnsignedCharDataType& dt) {
  printf("uchar");
}

void PrintDataType::accept(ShortDataType& dt) {
  printf("short");
}

void PrintDataType::accept(UnsignedShortDataType& dt) {
  printf("ushort");
}

void PrintDataType::accept(IntDataType& dt) {
  printf("int");
}

void PrintDataType::accept(UnsignedIntDataType& dt) {
  printf("uint");
}

void PrintDataType::accept(LongDataType& dt) {
  printf("long");
}

void PrintDataType::accept(UnsignedLongDataType& dt) {
  printf("ulong");
}

void PrintDataType::accept(LongLongDataType& dt) {
  printf("longlong");
}

void PrintDataType::accept(UnsignedLongLongDataType& dt) {
  printf("ulonglong");
}

void PrintDataType::accept(FloatDataType& dt) {
  printf("float");
}

void PrintDataType::accept(DoubleDataType& dt) {
  printf("double");
}

void PrintDataType::accept(LongDoubleDataType& dt) {
  printf("longdouble");
}

//
// Visit a pointer
//
void PrintDataType::accept(PointerDataType& dt) {
  printf("*");
  DataType::visit(dt.get_point_type(), *this);
}

//
// Visit an array
//
void PrintDataType::accept(ArrayDataType& dt) {

  static PrintExpression PRINT_EXPRESSION;

  printf("[");
  Expression::visit(dt.get_array_size(), PRINT_EXPRESSION);
  printf("]");
  DataType::visit(dt.get_array_type(), *this);
}

//
// Visit a function
//
void PrintDataType::accept(FunctionDataType& dt) {
  DataType::visit(dt.get_return_type(), *this);

  printf("(");

  // Print parameters
  auto list = dt.get_parameter_list();
  for (auto it = list.begin(); it != list.end(); ++it) {
    auto param = *it;
    DataType::visit(param.get_type(), *this);
    if (param.has_name()) { printf(" %s", param.get_name().c_str()); }
    if (it != std::prev(list.end())) { printf(", "); }
  }

  printf(")");
}
