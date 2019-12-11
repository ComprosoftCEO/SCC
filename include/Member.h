#ifndef MEMBER_HEADER
#define MEMBER_HEADER

#include <string>
#include <vector>

// Forward declare classes
class DataType;
class Expression;

/**
 * @class Member
 * Stores a single member (or entry) in a struct or union
 */
class Member final {

public:
  Member(DataType* type, const std::string& name);
  Member(DataType* type, const std::string& name, Expression* bitfield);
  Member(DataType* type, Expression* bitfield); /* For anonymous bitfield */
  ~Member();

  // Give members value semantics
  Member(const Member& other);
  Member& operator=(const Member& other);

  // Getters
  DataType* get_type() const;

  bool has_name() const;
  const std::string& get_name() const;

  bool is_bitfield() const;
  const Expression* get_bitfield_expression() const;

private:
  static void swap(Member& one, Member& two);

private:
  DataType* type;
  std::string name;     // Might be empty
  Expression* bitfield; // Might be null
};

typedef std::vector<Member> MemberList;

#endif /* Member Header Included */