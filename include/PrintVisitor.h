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

/**
 * @class ExpressionVisitor
 * Print an expression on one line, using parenthesis
 */
class PrintExpression final: public ExpressionVisitor {

public:
  void accept(CommaExpression& expr);
  void accept(AssignmentExpression& expr);
  void accept(CastExpression& expr);
  void accept(ConstantExpression& expr);
  void accept(StringExpression& expr);
  void accept(IdentifierExpression& expr);
  void accept(BracketExpression& expr);
  void accept(FunctionCallExpression& expr);
  void accept(MinusExpression& expr);
  void accept(NotExpression& expr);
  void accept(ComplementExpression& expr);
  void accept(DereferenceExpression& expr);
  void accept(AddressOfExpression& expr);
  void accept(SizeofExpression& expr);
  void accept(AlignofExpression& expr);
  void accept(AdditionExpression& expr);
  void accept(SubtractionExpression& expr);
  void accept(MultiplicationExpression& expr);
  void accept(DivisionExpression& expr);
  void accept(ModulusExpression& expr);
  void accept(LeftShiftExpression& expr);
  void accept(RightShiftExpression& expr);
  void accept(LessThanExpression& expr);
  void accept(GreaterThanExpression& expr);
  void accept(LessThanOrEqualExpression& expr);
  void accept(GreaterThanOrEqualExpression& expr);
  void accept(EqualsExpression& expr);
  void accept(NotEqualsExpression& expr);
  void accept(BitwiseAndExpression& expr);
  void accept(BitwiseOrExpression& expr);
  void accept(BitwiseXorExpression& expr);
  void accept(LogicalAndExpression& expr);
  void accept(LogicalOrExpression& expr);
  void accept(ConditionalExpression& expr);
};

/**
 * @class PrintStatement
 * Print the code stored in a statement
 */
class PrintStatement final: public StatementVisitor {

public:
  PrintStatement();

  void accept(EmptyStatement& stmt);
  void accept(DeclarationStatement& stmt);
  void accept(LabelStatement& stmt);
  void accept(CaseStatement& stmt);
  void accept(DefaultCaseStatement& stmt);
  void accept(CompoundStatement& stmt);
  void accept(ExpressionStatement& stmt);
  void accept(IfStatement& stmt);
  void accept(SwitchStatement& stmt);
  void accept(GotoStatement& stmt);
  void accept(WhileStatement& stmt);
  void accept(DoWhileStatement& stmt);
  void accept(ForStatement& stmt);
  void accept(ContinueStatement& stmt);
  void accept(BreakStatement& stmt);
  void accept(ReturnStatement& stmt);

  // Used for formatting with compound statements
  void visitIgnoreBrackets(class Statement* stmt);

private:
  int tabs;
  bool ignore_brackets; // For compound statements
};

#endif /* Print Visitor Header Included */
