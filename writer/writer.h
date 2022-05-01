#pragma once
#include "../file_utilities/file_working_utilities.h"
#include <string>

namespace file_handling {
void Write(const Image& image, const std::string& file);
void WriteImage(const Image& image, std::ofstream& output);
}  // namespace file_handling