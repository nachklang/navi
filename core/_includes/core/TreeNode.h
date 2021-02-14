#pragma once

#include <list>
#include <string>
#include <variant>

namespace navi
{

namespace core
{

using TreeValue = std::variant<int, double, std::string>;

namespace tags
{

enum class ValueTags
{
    INTEGER,
    DOUBLE,
    STRING
};

std::string toString(const tags::ValueTags& tag);
ValueTags fromString(const std::string& typeAsString);

} // namespace tags

class TreeNode
{

public:
    TreeNode();

    void put(const TreeValue& value);

    TreeNode* addChild(const TreeValue& value);
    void addChild(TreeNode* node);

    std::list<TreeNode*> children();

    TreeNode* parent();

    template <typename Value>
    Value get()
    {
        return std::get<Value>(m_value);
    }
    TreeValue getRaw();

private:
    TreeNode* m_parent;
    std::variant<int, double, std::string> m_value;
    std::list<TreeNode*> m_children;
};

} // namespace core

} // namespace navi
