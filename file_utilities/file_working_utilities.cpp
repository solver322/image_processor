#include "file_working_utilities.h"

int32_t GetPadding(const Image &image) {
    return image.GetWidth() % 4;
}

int32_t GetSize(const Image &image) {
    return image.GetHeight() * (3 * image.GetWidth() + GetPadding(image));
}