#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
std::string ElapsedTime(long times);  // TODO: See src/format.cpp
std::string ConvertToDoubleDigits(int number);
};                                    // namespace Format

#endif