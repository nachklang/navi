#pragma once

#include "core/TreeNode.h"

#include <string>
#include <variant>

namespace navi
{

namespace core
{


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

//Tree fromFile(const std::string& fileName);
//void toFile(const std::string& fileName, const Tree& tree);

} // namespace tree

} // namespace core

} // namespace navi
