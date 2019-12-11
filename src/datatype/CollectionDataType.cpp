#include <DataType.h>

//
// Constructor
//
CollectionDataType::CollectionDataType(CollectionType type, const MemberList& members):
  CollectionDataType(type, members, "") {}

CollectionDataType::CollectionDataType(CollectionType type, const std::string& name):
  DataType(ConcreteDataType::COLLECTION), type(type), incomplete_type(true), name(name) {}

CollectionDataType::CollectionDataType(CollectionType type, const MemberList& members,
                                       const std::string& name):
  DataType(ConcreteDataType::COLLECTION),
  type(type),
  incomplete_type(false),
  members(members),
  name(name) {}

//
// Getters
//
bool CollectionDataType::has_name() const {
  return this->name != "";
}

bool CollectionDataType::is_anonymous_struct() const {
  return this->has_name();
}

const std::string& CollectionDataType::get_name() const {
  return this->name;
}

bool CollectionDataType::is_incomplete_type() const {
  return this->incomplete_type;
}

const MemberList& CollectionDataType::get_members() const {
  return this->members;
}

//
// Underlying types
//
CollectionType CollectionDataType::get_collection_type() const {
  return this->type;
}

bool CollectionDataType::is_struct() const {
  return this->type == CollectionType::STRUCT;
}

bool CollectionDataType::is_union() const {
  return this->type == CollectionType::UNION;
}

//
// Update methods
//
void CollectionDataType::set_member_list(const MemberList& members) {
  this->members         = members;
  this->incomplete_type = false;
}

void CollectionDataType::set_name(const std::string& name) {
  this->name = name;
}
