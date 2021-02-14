#include "core/TreeNode.h"

#include <map>
#include <stdexcept>

namespace navi
{

namespace core
{

namespace
{

constexpr auto INTEGER = "integer";
constexpr auto DOUBLE = "double";
constexpr auto STRING = "string";

} // namespace

std::string tags::toString(const tags::ValueTags& tag)
{
    switch (tag)
    {
        case ValueTags::INTEGER: return INTEGER;
        case ValueTags::DOUBLE: return DOUBLE;
        case ValueTags::STRING: return STRING;
        default: throw std::runtime_error("Invalid data type tag");
    }
}

tags::ValueTags tags::fromString(const std::string& valueAsString)
{
    auto static tagValues = std::map<std::string, tags::ValueTags>{
        {INTEGER, tags::ValueTags::INTEGER},
        {DOUBLE, tags::ValueTags::DOUBLE},
        {STRING, tags::ValueTags::STRING}};

    return tagValues.at(valueAsString);
}

TreeNode::TreeNode() : m_parent(nullptr)
{
}

void TreeNode::put(const TreeValue& value)
{
    m_value = value;
}

TreeNode* TreeNode::addChild(const TreeValue& value)
{
    auto child = new TreeNode();
    child->m_parent = this;
    child->put(value);
    m_children.push_back(child);

    return child;
}

void TreeNode::addChild(TreeNode* node)
{
    if (node != nullptr)
    {
        node->m_parent = this;
        m_children.push_back(node);
    }
}

std::list<TreeNode*> TreeNode::children()
{
    return m_children;
}

TreeNode* TreeNode::parent()
{
    return m_parent;
}

TreeValue TreeNode::getRaw()
{
    return m_value;
}

} // namespace core

} // namespace navi