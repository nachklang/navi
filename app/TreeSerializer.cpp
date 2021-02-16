#include "TreeSerializer.h"

#include "json.hpp"

#include <fstream>
#include <sstream>

#include <iostream>

using json = nlohmann::json;

using namespace navi::core;

namespace
{

void insertValue(json& object, const TreeValue& value)
{
    auto type = static_cast<tags::ValueTags>(value.index());

    switch (type)
    {
        case tags::ValueTags::INTEGER:
        {
            auto extracted = std::get<int>(value);
            object["value"] = extracted;
            break;
        }

        case tags::ValueTags::DOUBLE:
        {
            auto extracted = std::get<double>(value);
            object["value"] = extracted;
            break;
        }

        case tags::ValueTags::STRING:
        {
            auto extracted = std::get<std::string>(value);
            object["value"] = extracted;
            break;
        }
    }
}

void insertValue(TreeNode* node, const json::iterator& val)
{
    if (val->is_number())
    {
        int value = *val;
        node->put(value);
    }

    if (val->is_number_float())
    {
        double value = *val;
        node->put(value);
    }

    if (val->is_string())
    {
        std::string value = *val;
        node->put(value);
    }
}

bool insertIfExists(TreeNode* node, const std::reference_wrapper<json>& val)
{
    auto rawValue = val.get().find("value");

    if (rawValue != val.get().end())
    {
        insertValue(node, rawValue);
        return true;
    }
    return false;
}

bool hasValue(const json& object)
{
    return object.find("value") != object.end();
}

} // namespace

namespace navi
{

namespace serialize
{

core::Tree* fromFile(const std::string& fileName)
{
    std::ifstream stream(fileName.c_str());
    if (stream.good())
    {
        json object = json::parse(stream);
        auto children = std::stack<std::pair<json&, TreeNode*>>{};

        if (object.empty())
        {
            return nullptr;
        }

        auto tree = new Tree();
        auto root = tree->getRoot();

        auto* item = root;
        auto jsonItem = std::ref(object);

        auto valueExists = hasValue(jsonItem);

        while (valueExists)
        {
            insertIfExists(item, jsonItem);

            auto jsonChildren = jsonItem.get().find("children");
            bool hasChildren = jsonChildren != jsonItem.get().end();

            if (hasChildren)
            {
                std::for_each(
                    jsonChildren->rbegin(),
                    jsonChildren->rend(),
                    [&children, item](auto& node) {
                        auto treeNode = new TreeNode();
                        children.push({node, item->addChild(treeNode)});
                    });
            }

            if (!children.empty())
            {
                auto pair = children.top();

                jsonItem = pair.first;
                item = pair.second;
                children.pop();
            }
            else
            {
                valueExists = false;
            }
        }
        return tree;
    }

    return nullptr;
}

void toFile(const std::string& fileName, core::Tree& tree)
{
    using namespace navi::core;

    auto root = tree.getRoot();
    if (fileName.empty() || root == nullptr)
    {
        return;
    }

    auto children = std::stack<std::pair<TreeNode*, json::reference>>{};
    auto* item = root;
    json object;
    auto jsonItem = std::ref(object);

    while (item)
    {
        insertValue(jsonItem, item->getRaw());

        const auto& itemChildren = item->children();
        if (itemChildren.size())
        {

            jsonItem.get().operator[]("children") = json::array({});
            auto& arrRef = jsonItem.get().operator[]("children");

            size_t counter = 0;
            while (counter < itemChildren.size())
            {
                json obj = json::object();
                arrRef.push_back(obj);
                ++counter;
            }

            auto jsonIt = arrRef.begin();
            for (auto rbegin = itemChildren.rbegin();
                 rbegin != itemChildren.rend();
                 ++rbegin)
            {
                json::reference ref = *jsonIt;
                children.push({*rbegin, ref});
                ++jsonIt;
            }
        }
        item = nullptr;

        if (!children.empty())
        {
            auto pair = children.top();
            item = pair.first;
            jsonItem = pair.second;
            children.pop();
        }
    }
    std::ofstream outFile;
    outFile.open(fileName);
    outFile << object.dump(4);
}

} // namespace serialize

} // namespace navi
