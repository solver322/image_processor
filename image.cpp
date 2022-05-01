#include "image.h"

Image::Image(int32_t height, int32_t width)
    : height_(height), width_(width), image_(std::vector<std::vector<Pixel>>(height, std::vector<Pixel>(width))) {
}

void Image::SetPixel(int32_t y, int32_t x, const Pixel& pixel) {
    if (y < 0 || y >= height_) {
        return;
    }
    if (x < 0 || x >= width_) {
        return;
    }
    image_[y][x] = {.red = pixel.red, .green = pixel.green, .blue = pixel.blue};
}

Pixel Image::GetPixel(int32_t y, int32_t x) const {
    if (y >= height_) {
        y = height_ - 1;
    } else if (y < 0) {
        y = 0;
    }
    if (x >= width_) {
        x = width_ - 1;
    } else if (x < 0) {
        x = 0;
    }
    return image_[y][x];
}

int32_t Image::GetHeight() const {
    return height_;
}

int32_t Image::GetWidth() const {
    return width_;
}
