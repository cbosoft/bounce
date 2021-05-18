#include <algorithm>
#include <bounce/transform/transform.hpp>

static std::hash<std::string> string_hasher;

bool Transform::is_a(const std::string &tag) const
{
    std::size_t tag_hash = string_hasher(tag);
    return this->is_a(tag_hash);
}

bool Transform::is_a(std::size_t tag_hash) const
{
    auto it = std::find(this->_tag_hashes.begin(), this->_tag_hashes.end(), tag_hash);
    return it != this->_tag_hashes.end();
}

void Transform::add_tag(const std::string &tag)
{
    this->_tags.push_back(tag);
    this->add_tag(string_hasher(tag));
}

void Transform::add_tag(std::size_t tag_hash)
{
    this->_tag_hashes.push_back(tag_hash);
    this->_tag_hashes.sort();
    this->_tag_hashes.unique();
}

void Transform::find_in_children(const std::string &tag, std::list<Transform *> &out) const
{
    this->find_in_children(string_hasher(tag), out);
}

void Transform::find_in_children(std::size_t tag_hash, std::list<Transform *> &out) const
{
    for (auto *child : this->_children) {
        if (child->is_a(tag_hash)) {
            out.push_back(child);
        }
        child->find_in_children(tag_hash, out);
    }
}
