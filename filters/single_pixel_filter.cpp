#include "single_pixel_filter.h"

Image SinglePixelFilter::Apply(const Image& image) const {
    Image result_image(image.GetHeight(), image.GetWidth());
    for (int32_t i = 0; i < image.GetHeight(); ++i) {
        for (int32_t j = 0; j < image.GetWidth(); ++j) {
            result_image.SetPixel(i, j, ChangePixel(image.GetPixel(i, j)));
        }
    }
    return result_image;
}