#include "matrix_filter.h"

MatrixFilter::MatrixFilter(const std::vector<std::vector<double>>& matrix)
    : h_radius_(matrix.size() / 2), w_radius_(matrix[0].size() / 2), matrix_(matrix) {
}

Image MatrixFilter::Apply(const Image& image) const {
    Image result_image(image.GetHeight(), image.GetWidth());
    for (int32_t i = 0; i < image.GetHeight(); ++i) {
        for (int32_t j = 0; j < image.GetWidth(); ++j) {
            Pixel result_pixel = CalculatePixel(image, i, j);
            result_image.SetPixel(i, j, result_pixel);
        }
    }
    return result_image;
}

Pixel MatrixFilter::CalculatePixel(const Image& image, const int32_t& i, const int32_t& j) const{
    double red = 0;
    double green = 0;
    double blue = 0;
    for (int32_t h_offset = 0; h_offset <= 2 * h_radius_; ++h_offset) {
        for (int32_t w_offset = 0; w_offset <= 2 * w_radius_; ++w_offset) {
            Pixel current_pixel = image.GetPixel(i - h_offset + h_radius_, j + w_offset - w_radius_);
            red += matrix_[h_offset][w_offset] * current_pixel.red;
            green += matrix_[h_offset][w_offset] * current_pixel.green;
            blue += matrix_[h_offset][w_offset] * current_pixel.blue;
        }
    }
    Pixel result_pixel;
    result_pixel.red = std::max(0.0, std::min(255.0, red));
    result_pixel.green = std::max(0.0, std::min(255.0, green));
    result_pixel.blue = std::max(0.0, std::min(255.0, blue));
    return result_pixel;
}