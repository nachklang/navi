#pragma once

#include "core/Tree.h"

namespace navi
{

namespace serialize
{

core::Tree* fromFile(const std::string& fileName);
void toFile(const std::string& fileName, core::Tree& tree);

} // namespace serialize

} // namespace navi
