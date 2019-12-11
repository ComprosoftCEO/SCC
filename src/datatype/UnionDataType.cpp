#include <DataType.h>
#include <Visitor.h>

//
// Constructor
//
UnionDataType::UnionDataType(const MemberList& members):
  CollectionDataType(CollectionType::UNION, members) {}

UnionDataType::UnionDataType(const std::string& name):
  CollectionDataType(CollectionType::UNION, name) {}

UnionDataType::UnionDataType(const MemberList& members, const std::string& name):
  CollectionDataType(CollectionType::UNION, members, name) {}

//
// Get the size
//
size_t UnionDataType::size() const {
  size_t max_size = 0;
  if (this->is_incomplete_type()) { return max_size; /* Not known */ }

  const auto members = this->get_members();
  for (auto member: members) {
    const size_t member_size = member.get_type()->size();
    if (member_size > max_size) { max_size = member_size; }
  }

  return max_size;
}

//
// Visit
//
void UnionDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
UnionDataType* UnionDataType::clone() const {
  if (this->is_incomplete_type()) { return new UnionDataType(this->name); }
  return new UnionDataType(this->members, this->name);
}
