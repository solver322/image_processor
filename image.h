#pragma once
#include <cstdint>
#include <vector>

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class Image {
public:
    Image(int32_t height, int32_t width);
    void SetPixel(int32_t y, int32_t x, const Pixel& pixel);
    Pixel GetPixel(int32_t y, int32_t x) const;
    int32_t GetHeight() const;
    int32_t GetWidth() const;

private:
    int32_t height_;
    int32_t width_;
    std::vector<std::vector<Pixel>> image_;
};