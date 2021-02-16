#pragma once

#include "core/Tree.h"

namespace navi
{

namespace serialize
{

// core::Tree* fromFile(const std::string& fileName);
void toFile(const std::string& fileName, core::Tree& tree);

} // namespace serialize

} // namespace navi

template <typename Writer>
void writeValue(Writer& writer, const navi::core::TreeValue& value)
{
    using namespace navi::core;
    auto type = value.index();
    switch (static_cast<tags::ValueTags>(type))
    {
        case tags::ValueTags::INTEGER:
            writer.write("val", std::get<int>(value));
            break;
        case tags::ValueTags::DOUBLE:
            writer.write("val", std::get<double>(value));
            break;
        case tags::ValueTags::STRING:
            writer.write("val", std::get<std::string>(value));
            break;
    }
}
