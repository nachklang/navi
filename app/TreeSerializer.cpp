#include "TreeSerializer.h"

#include "json.hpp"

#include <fstream>
#include <sstream>

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

} // namespace

namespace navi
{

namespace serialize
{

// core::Tree* fromFile(const std::string& fileName)
//{
//}

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
