#pragma once
#include "../file_utilities/file_working_utilities.h"
#include <string>

namespace file_handling {
Image Read(const std::string &file);
void ReadImage(std::ifstream &input, Image &result_image);

}  // namespace file_utilities