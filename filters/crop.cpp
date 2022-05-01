#include "crop.h"

Crop::Crop(int32_t height, int32_t width) : height_(height), width_(width) {
}

Image Crop::Apply(const Image& image) const {
    Image result_image(std::min(height_, image.GetHeight()), std::min(width_, image.GetWidth()));
    int32_t h_offset = 0;
    if (result_image.GetHeight() < image.GetHeight()) {
        h_offset = image.GetHeight() - result_image.GetHeight();
    }
    for (int32_t i = 0; i < result_image.GetHeight(); ++i) {
        for (int32_t j = 0; j < result_image.GetWidth(); ++j) {
            result_image.SetPixel(i, j, image.GetPixel(i + h_offset, j));
        }
    }
    return result_image;
}