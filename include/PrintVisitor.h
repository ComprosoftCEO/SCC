#ifndef PRINT_VISITOR_HEADER
#define PRINT_VISITOR_HEADER

#include <Visitor.h>

/**
 * @class PrintDataType
 * Prints out a DataType on one line
 */
class PrintDataType final: public DataTypeVisitor {

public:
  void accept(VoidDataType& dt);
  void accept(CharDataType& dt);
  void accept(UnsignedCharDataType& dt);
  void accept(ShortDataType& dt);
  void accept(UnsignedShortDataType& dt);
  void accept(IntDataType& dt);
  void accept(UnsignedIntDataType& dt);
  void accept(LongDataType& dt);
  void accept(UnsignedLongDataType& dt);
  void accept(LongLongDataType& dt);
  void accept(UnsignedLongLongDataType& dt);
  void accept(FloatDataType& dt);
  void accept(DoubleDataType& dt);
  void accept(LongDoubleDataType& dt);
  void accept(PointerDataType& dt);
  void accept(ArrayDataType& dt);
  void accept(FunctionDataType& dt);
};

#endif /* Print Visitor Header Included */
