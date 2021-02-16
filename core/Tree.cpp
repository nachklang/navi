#include "core/Tree.h"
#include "core/TreeNode.h"

namespace navi
{

namespace core
{

Tree::Tree() : m_root(new TreeNode())
{
}

TreeNode* Tree::getRoot()
{
    return m_root;
}

void Tree::put(const TreeValue& value)
{
    m_root->put(value);
}

TreeNode* Tree::addChild(const TreeValue& value)
{
    return m_root->addChild(value);
}

void Tree::addChild(TreeNode* node)
{
    m_root->addChild(node);
}

Tree::~Tree()
{
    tree::process<TreeNodeProcessor>(m_root, [](auto* item) { delete item; });
}

} // namespace core

} // namespace navi
