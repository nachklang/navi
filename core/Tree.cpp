#include "core/Tree.h"
#include "core/TreeNode.h"

namespace navi
{

namespace core
{

namespace tree
{

//Tree fromFile(const std::string& fileName)
//{
//}

//void toFile(const std::string& fileName, const Tree& tree)
//{
//}

} // namespace tree

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
}

// namespace tree

} // namespace core

} // namespace navi
