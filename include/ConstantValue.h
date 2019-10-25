#ifndef CONSTANT_VALUE_HEADER
#define CONSTANT_VALUE_HEADER

#include <cstdint>

enum class ConstantValueType { INT_32, INT_64, UINT_32, UINT_64, FLOAT, DOUBLE };

/**
 * Class that stores a constant, like 1 or 3.5
 */
class ConstantValue final {

public:
  explicit ConstantValue(int32_t value);
  explicit ConstantValue(int64_t value);
  explicit ConstantValue(uint32_t value);
  explicit ConstantValue(uint64_t value);
  explicit ConstantValue(float value);
  explicit ConstantValue(double value);

  ConstantValueType current_type() const;

  // Conversion
  int8_t to_char() const;
  uint8_t to_uchar() const;
  int16_t to_short() const;
  uint16_t to_ushort() const;
  int32_t to_int() const;
  uint32_t to_uint() const;
  int64_t to_long() const;
  uint64_t to_ulong() const;
  int64_t to_longlong() const;
  uint64_t to_ulonglong() const;
  float to_float() const;
  double to_double() const;

  // Modifies the two parameters being passed in
  static void upcast(ConstantValueType& one, ConstantValueType& two);

  // Binary math operations
  static ConstantValueType add(ConstantValueType one, ConstantValueType two);
  static ConstantValueType subtract(ConstantValueType one, ConstantValueType two);
  static ConstantValueType multiply(ConstantValueType one, ConstantValueType two);
  static ConstantValueType divide(ConstantValueType one, ConstantValueType two);

private:
  union {
    int32_t i32_val;
    int64_t i64_val;
    uint32_t u32_val;
    uint64_t u64_val;
    float f32_val;
    double f64_val;
  } value;
  ConstantValueType type;
};

#endif /* Constant Value Included */