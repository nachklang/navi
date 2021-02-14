#include "core/Tree.h"

#include "CLI11.hpp"

#include <iostream>
#include <string>
#include <variant>

struct printValue
{
    template <typename T>
    void operator()(const T& value) const
    {
        std::cout << value;
    }
};

namespace
{

navi::core::Tree* generateTestTree()
{
    auto tree = new navi::core::Tree();
    tree->put(8);
    auto bar = tree->addChild("bar");

    auto double_2_015 = bar->addChild(2.015);
    double_2_015->addChild(9);

    bar->addChild(2015);
    bar->addChild("2015");

    auto baz = tree->addChild("baz");

    baz->addChild("foo");
    auto double_6_238 = baz->addChild(6.28318);
    double_6_238->addChild("hello");

    return tree;
}

std::string getNodeName(navi::core::TreeNode* node)
{
    return node->parent() == nullptr ? "Root" : "Node";
}

std::string createSpacignLine(int spacing)
{
    return std::string((spacing)*2, '-');
}

void printNodeValue(navi::core::TreeNode* root)
{
    auto raw = root->getRaw();
    std::cout << createSpacignLine(root->spacing()) << getNodeName(root) << "(";
    std::visit(printValue{}, root->getRaw());
    std::cout << "||"
              << navi::core::tags::toString(
                     static_cast<navi::core::tags::ValueTags>(raw.index()))
              << ")" << std::endl;
}

void printTree(navi::core::Tree& tree)
{
    using namespace navi::core;
    auto root = tree.getRoot();

    tree::process<TreeNodeProcessor>(root, [](auto* item) {
        printNodeValue(item);
    });
}

void printTestTree()
{
    auto tree = generateTestTree();
    printTree(*tree);
    delete tree;
}

} // namespace

int main(int argc, char** argv)
{
    CLI::App app{"Tree "};

    std::string inputFileName = {};
    std::string outputFileName = {};

    app.add_option("-i", inputFileName);
    app.add_option("-o", outputFileName);

    app.add_flag_function("-t,--test", [](const auto&) {
        printTestTree();
    });

    CLI11_PARSE(app, argc, argv);
}
