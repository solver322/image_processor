#pragma once
#include "filter.h"

class MatrixFilter : public Filter {
public:
    MatrixFilter(const std::vector<std::vector<double>> &matrix);
    Image Apply(const Image &prepared_image) const override;

private:
    Pixel CalculatePixel(const Image &image, const int32_t &i, const int32_t &j) const;
    const int32_t h_radius_;
    const int32_t w_radius_;
    const std::vector<std::vector<double>> matrix_;
};
