#include <DataType.h>
#include <Visitor.h>

//
// Constructor
//
StructDataType::StructDataType(const MemberList& members):
  CollectionDataType(CollectionType::STRUCT, members) {}

StructDataType::StructDataType(const std::string& name):
  CollectionDataType(CollectionType::STRUCT, name) {}

StructDataType::StructDataType(const MemberList& members, const std::string& name):
  CollectionDataType(CollectionType::STRUCT, members, name) {}

//
// Get the size
//
size_t StructDataType::size() const {
  size_t total_size = 0;
  if (this->is_incomplete_type()) { return total_size; /* Not known */ }

  auto members = this->get_members();
  for (auto member: members) { total_size += member.get_type()->size(); }

  return total_size;
}

//
// Visit
//
void StructDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
StructDataType* StructDataType::clone() const {
  if (this->is_incomplete_type()) { return new StructDataType(this->name); }
  return new StructDataType(this->members, this->name);
}
