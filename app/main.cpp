#include "core/Tree.h"

#include <iostream>
#include <string>
#include <variant>

#include <algorithm>

struct printVar
{
    template <typename T>
    void operator()(const T& value) const
    {
        std::cout << value;
    }
};

namespace
{

navi::core::Tree generateTestTree()
{
    auto tree = navi::core::Tree();
    tree.put(8);
    auto bar = tree.addChild("bar");

    auto double_2_015 = bar->addChild(2.015);
    double_2_015->addChild(9);

    bar->addChild(2015);
    bar->addChild("2015");

    auto baz = tree.addChild("baz");

    baz->addChild("foo");
    auto double_6_238 = baz->addChild(6.28318);
    double_6_238->addChild("hello");

    return tree;
}

std::string getNodeName(navi::core::TreeNode* node)
{
    return node->parent() == nullptr ? "Root" : "Node";
}

void printSubtrees(navi::core::TreeNode* root, int spacing)
{
    auto levelString = std::string((spacing)*2, '-');

    auto raw = root->getRaw();
    std::cout << levelString << getNodeName(root) << "(";
    std::visit(printVar{}, root->getRaw());
    std::cout << "||"
              << navi::core::tags::toString(
                     static_cast<navi::core::tags::ValueTags>(raw.index()))
              << ")" << std::endl;

    ++spacing;
    for (auto& child: root->children())
    {

        printSubtrees(child, spacing);
    }
}

void printTree(navi::core::Tree& tree)
{
    auto root = tree.getRoot();
    printSubtrees(root, 0);
}

} // namespace

int main()
{
    auto tree = generateTestTree();
    printTree(tree);
}
