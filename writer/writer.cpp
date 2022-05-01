#include "writer.h"
#include "fstream"

const std::string BMP_ID = "BM";
const int32_t HEADER_SIZE = 54;
const int16_t UNUSED_GAP = 0;
const int32_t DIB_SIZE = 40;
const int16_t NUMBER_OF_COLOR_PLANES = 1;
const int16_t BITS_PER_PIXEL = 24;
const int32_t BI_RGB = 0;
const int32_t PRINT_RESOLUTION = 2835;
const int32_t NUM_OF_COLORS_IN_PALETTE = 0;
const int32_t IMPORTANT_COLORS = 0;

const size_t COLOR_SIZE = 1;
const std::string PROBABLY_PADDING = "0000";

template <typename T>
void FWrite(std::ofstream &file, const T &number) {
    file.write(reinterpret_cast<const char *>(&number), sizeof(number));
}

template <>
void FWrite(std::ofstream &file, const std::string &str) {
    file.write(str.c_str(), str.length());
}

void file_handling::WriteImage(const Image &image, std::ofstream &output) {
    int32_t padding_size = GetPadding(image);
    std::string file_padding = std::string(PROBABLY_PADDING, 0, padding_size);

    for (int32_t i = 0; i < image.GetHeight(); ++i) {
        for (int32_t j = 0; j < image.GetWidth(); ++j) {
            Pixel pixel = image.GetPixel(i, j);
            FWrite(output, pixel.blue);
            FWrite(output, pixel.green);
            FWrite(output, pixel.red);
        }
        FWrite(output, file_padding);
    }
}

void file_handling::Write(const Image &image, const std::string &file) {
    std::ofstream output(file, std::ios::out | std::ios::binary);

    if (!output.is_open()) {
        throw "can't open file for write";
    }

    FWrite(output, BMP_ID);
    int32_t pixel_array_size = GetSize(image);
    int32_t file_size = HEADER_SIZE + pixel_array_size;
    FWrite(output, file_size);
    FWrite(output, UNUSED_GAP);
    FWrite(output, UNUSED_GAP);
    FWrite(output, HEADER_SIZE);
    FWrite(output, DIB_SIZE);

    int32_t width = image.GetWidth();
    FWrite(output, width);

    int32_t height = image.GetHeight();
    FWrite(output, height);

    FWrite(output, NUMBER_OF_COLOR_PLANES);
    FWrite(output, BITS_PER_PIXEL);
    FWrite(output, BI_RGB);
    FWrite(output, pixel_array_size);
    FWrite(output, PRINT_RESOLUTION);
    FWrite(output, PRINT_RESOLUTION);
    FWrite(output, NUM_OF_COLORS_IN_PALETTE);
    FWrite(output, IMPORTANT_COLORS);

    WriteImage(image, output);

    output.close();
}