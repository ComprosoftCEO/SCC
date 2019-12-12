#ifndef VISITOR_HEADER
#define VISITOR_HEADER

// Forward declare the expression clases
class CommaExpression;
class AssignmentExpression;
class CastExpression;
class ConstantExpression;
class StringExpression;
class IdentifierExpression;
class BracketExpression;
class FunctionCallExpression;
class MinusExpression;
class NotExpression;
class ComplementExpression;
class DereferenceExpression;
class AddressOfExpression;
class SizeofExpression;
class AlignofExpression;
class AdditionExpression;
class SubtractionExpression;
class MultiplicationExpression;
class DivisionExpression;
class ModulusExpression;
class LeftShiftExpression;
class RightShiftExpression;
class LessThanExpression;
class GreaterThanExpression;
class LessThanOrEqualExpression;
class GreaterThanOrEqualExpression;
class EqualsExpression;
class NotEqualsExpression;
class BitwiseAndExpression;
class BitwiseOrExpression;
class BitwiseXorExpression;
class LogicalAndExpression;
class LogicalOrExpression;
class ConditionalExpression;

// Forward declare all of the statement classes
class EmptyStatement;
class DeclarationStatement;
class LabelStatement;
class CaseStatement;
class DefaultCaseStatement;
class CompoundStatement;
class ExpressionStatement;
class IfStatement;
class SwitchStatement;
class GotoStatement;
class WhileStatement;
class DoWhileStatement;
class ForStatement;
class ContinueStatement;
class BreakStatement;
class ReturnStatement;

// Forward declare all of the data type classes
class VoidDataType;
class CharDataType;
class UnsignedCharDataType;
class ShortDataType;
class UnsignedShortDataType;
class IntDataType;
class UnsignedIntDataType;
class LongDataType;
class UnsignedLongDataType;
class LongLongDataType;
class UnsignedLongLongDataType;
class FloatDataType;
class DoubleDataType;
class LongDoubleDataType;
class PointerDataType;
class ArrayDataType;
class FunctionDataType;
class StructDataType;
class UnionDataType;
class EnumDataType;

/**
 * @class ExpressionVisitor
 * Visitor interface for all expression objects. Has a default
 *   accept implementation to make concrete implementations easier.
 */
class ExpressionVisitor {

public:
  virtual ~ExpressionVisitor() = default;

  virtual void accept(CommaExpression& expr);
  virtual void accept(AssignmentExpression& expr);
  virtual void accept(CastExpression& expr);
  virtual void accept(ConstantExpression& expr);
  virtual void accept(StringExpression& expr);
  virtual void accept(IdentifierExpression& expr);
  virtual void accept(BracketExpression& expr);
  virtual void accept(FunctionCallExpression& expr);
  virtual void accept(MinusExpression& expr);
  virtual void accept(NotExpression& expr);
  virtual void accept(ComplementExpression& expr);
  virtual void accept(DereferenceExpression& expr);
  virtual void accept(AddressOfExpression& expr);
  virtual void accept(SizeofExpression& expr);
  virtual void accept(AlignofExpression& expr);
  virtual void accept(AdditionExpression& expr);
  virtual void accept(SubtractionExpression& expr);
  virtual void accept(MultiplicationExpression& expr);
  virtual void accept(DivisionExpression& expr);
  virtual void accept(ModulusExpression& expr);
  virtual void accept(LeftShiftExpression& expr);
  virtual void accept(RightShiftExpression& expr);
  virtual void accept(LessThanExpression& expr);
  virtual void accept(GreaterThanExpression& expr);
  virtual void accept(LessThanOrEqualExpression& expr);
  virtual void accept(GreaterThanOrEqualExpression& expr);
  virtual void accept(EqualsExpression& expr);
  virtual void accept(NotEqualsExpression& expr);
  virtual void accept(BitwiseAndExpression& expr);
  virtual void accept(BitwiseOrExpression& expr);
  virtual void accept(BitwiseXorExpression& expr);
  virtual void accept(LogicalAndExpression& expr);
  virtual void accept(LogicalOrExpression& expr);
  virtual void accept(ConditionalExpression& expr);
};

/**
 * @class StatementVisitor
 * Visitor interface for all statement objects. Has a default
 *   accept implementation to make concrete implementations easier.
 */
class StatementVisitor {

public:
  virtual ~StatementVisitor() = default;

  virtual void accept(EmptyStatement& stmt);
  virtual void accept(DeclarationStatement& stmt);
  virtual void accept(LabelStatement& stmt);
  virtual void accept(CaseStatement& stmt);
  virtual void accept(DefaultCaseStatement& stmt);
  virtual void accept(CompoundStatement& stmt);
  virtual void accept(ExpressionStatement& stmt);
  virtual void accept(IfStatement& stmt);
  virtual void accept(SwitchStatement& stmt);
  virtual void accept(GotoStatement& stmt);
  virtual void accept(WhileStatement& stmt);
  virtual void accept(DoWhileStatement& stmt);
  virtual void accept(ForStatement& stmt);
  virtual void accept(ContinueStatement& stmt);
  virtual void accept(BreakStatement& stmt);
  virtual void accept(ReturnStatement& stmt);
};

/**
 * @class DataTypeVisitor
 * Visitor interface for the DataType objects
 */
class DataTypeVisitor {

public:
  virtual ~DataTypeVisitor() = default;

  virtual void accept(VoidDataType& dt);
  virtual void accept(CharDataType& dt);
  virtual void accept(UnsignedCharDataType& dt);
  virtual void accept(ShortDataType& dt);
  virtual void accept(UnsignedShortDataType& dt);
  virtual void accept(IntDataType& dt);
  virtual void accept(UnsignedIntDataType& dt);
  virtual void accept(LongDataType& dt);
  virtual void accept(UnsignedLongDataType& dt);
  virtual void accept(LongLongDataType& dt);
  virtual void accept(UnsignedLongLongDataType& dt);
  virtual void accept(FloatDataType& dt);
  virtual void accept(DoubleDataType& dt);
  virtual void accept(LongDoubleDataType& dt);
  virtual void accept(PointerDataType& dt);
  virtual void accept(ArrayDataType& dt);
  virtual void accept(FunctionDataType& dt);
  virtual void accept(StructDataType& dt);
  virtual void accept(UnionDataType& dt);
  virtual void accept(EnumDataType& dt);
};

#endif /* Visitor Header Included */