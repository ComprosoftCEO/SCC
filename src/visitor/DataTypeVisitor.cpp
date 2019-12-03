#include <DataType.h>
#include <Visitor.h>

//
// Accept for primitive types does nothing
//
void DataTypeVisitor::accept(VoidDataType& dt) {}
void DataTypeVisitor::accept(CharDataType& dt) {}
void DataTypeVisitor::accept(UnsignedCharDataType& dt) {}
void DataTypeVisitor::accept(ShortDataType& dt) {}
void DataTypeVisitor::accept(UnsignedShortDataType& dt) {}
void DataTypeVisitor::accept(IntDataType& dt) {}
void DataTypeVisitor::accept(UnsignedIntDataType& dt) {}
void DataTypeVisitor::accept(LongDataType& dt) {}
void DataTypeVisitor::accept(UnsignedLongDataType& dt) {}
void DataTypeVisitor::accept(LongLongDataType& dt) {}
void DataTypeVisitor::accept(UnsignedLongLongDataType& dt) {}
void DataTypeVisitor::accept(FloatDataType& dt) {}
void DataTypeVisitor::accept(DoubleDataType& dt) {}
void DataTypeVisitor::accept(LongDoubleDataType& dt) {}

//
// Visit complex types
//
void DataTypeVisitor::accept(PointerDataType& dt) {
  DataType::visit(dt.get_point_type(), *this);
}

void DataTypeVisitor::accept(ArrayDataType& dt) {
  DataType::visit(dt.get_array_type(), *this);
}

void DataTypeVisitor::accept(FunctionDataType& dt) {
  for (auto param: dt.get_parameter_list()) { DataType::visit(param.get_type(), *this); }
  DataType::visit(dt.get_return_type(), *this);
}
