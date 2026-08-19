#include "ViewUtils.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace {

using Lines = std::vector<std::string>;

Lines wrap(const char* text, int width)
{
    Lines lines;
    const int count = pdg::app::detail::forEachWrappedLine(
        text,
        width,
        [](const std::string&, std::size_t length) {
            return static_cast<int>(length);
        },
        [&lines](const std::string& line) {
            lines.push_back(line);
        });

    if (count != static_cast<int>(lines.size())) {
        std::cerr << "line count did not match emitted lines\n";
        std::exit(EXIT_FAILURE);
    }
    return lines;
}

void expectLines(const char* testName, const Lines& actual, const Lines& expected)
{
    if (actual == expected) {
        return;
    }

    std::cerr << testName << " failed\n  expected:";
    for (const std::string& line : expected) {
        std::cerr << " [" << line << ']';
    }
    std::cerr << "\n  actual:  ";
    for (const std::string& line : actual) {
        std::cerr << " [" << line << ']';
    }
    std::cerr << '\n';
    std::exit(EXIT_FAILURE);
}

} // namespace

int main()
{
    expectLines("null text", wrap(nullptr, 10), {});
    expectLines("empty text", wrap("", 10), {""});
    expectLines("text that fits", wrap("settlers", 10), {"settlers"});
    expectLines("hard line breaks", wrap("one|two|three", 20), {"one", "two", "three"});
    expectLines("leading hard line break", wrap("|two", 20), {"", "two"});
    expectLines("word wrapping", wrap("alpha beta", 6), {"alpha ", "beta"});
    expectLines("hyphen wrapping", wrap("well-known", 5), {"well-", "known"});
    expectLines("long word wrapping", wrap("abcdef", 3), {"abc", "def"});
    expectLines("narrow area still progresses", wrap("abc", 0), {"a", "b", "c"});

    std::cout << "ViewUtils tests passed\n";
    return EXIT_SUCCESS;
}
