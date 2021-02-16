#pragma once

#include "core/TreeNode.h"

#include <algorithm>
#include <functional>
#include <stack>
#include <string>
#include <variant>

namespace navi
{

namespace core
{

using TreeNodeProcessor = std::function<void(TreeNode*)>;

class Tree
{

public:
    Tree();
    TreeNode* getRoot();
    void put(const TreeValue& value);
    TreeNode* addChild(const TreeValue& value);
    void addChild(TreeNode* node);
    ~Tree();

private:
    TreeNode* m_root;
};

namespace tree
{

template <typename Processor>
void process(TreeNode* root, const Processor& processor)
{
    auto children = std::stack<navi::core::TreeNode*>{};
    auto* item = root;

    while (item)
    {
        const auto& itemChildren = item->children();
        std::for_each(
            itemChildren.rbegin(),
            itemChildren.rend(),
            [&children](auto* child) { children.push(child); });

        processor(item);
        item = nullptr;

        if (!children.empty())
        {
            item = children.top();
            children.pop();
        }
    }
}

} // namespace tree

} // namespace core

} // namespace navi
