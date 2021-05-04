#include <bounce/object/object.hpp>

bool Object::is_a(const std::string &s) const
{
    std::size_t hash_s = std::hash<std::string>{}(s);
    return this->_type_identifier == hash_s;
}

void Object::set_identifier(const std::string &s)
{
    this->_type_identifier = std::hash<std::string>{}(s);
}