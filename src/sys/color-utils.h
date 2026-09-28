// Shared internal CSS parser used by Color and the native script bindings.
#ifndef PDG_COLOR_UTILS_H_INCLUDED
#define PDG_COLOR_UTILS_H_INCLUDED

#include "pdg/sys/color.h"
#include <string_view>

namespace pdg {
// Invalid input leaves the output unchanged, including invalid spellings of black.
bool parseCssColor(std::string_view text, Color& color);
}

#endif
