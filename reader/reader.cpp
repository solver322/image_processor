#include "reader.h"
#include <fstream>

const size_t SIZE_OF_BMP_HEADER = 14;
const size_t DEFAULT_DATA_SIZE = 4;
const int32_t SIZE_OF_HEADER = 54;

template <typename T>
void FRead(std::ifstream &file, T &number) {
    file.read(reinterpret_cast<char *>(&number), sizeof(number));
}

void file_handling::ReadImage(std::ifstream &input, Image &result_image) {
    input.seekg(SIZE_OF_HEADER, std::ios::beg);

    int32_t padding = GetPadding(result_image);

    for (int32_t i = 0; i < result_image.GetHeight(); ++i) {
        for (int32_t j = 0; j < result_image.GetWidth(); ++j) {
            Pixel pixel;
            FRead(input, pixel.blue);
            FRead(input, pixel.green);
            FRead(input, pixel.red);
            result_image.SetPixel(i, j, pixel);
        }
        input.seekg(padding, std::ios::cur);
    }
}

Image file_handling::Read(const std::string &file) {
    std::ifstream input(file, std::ios::in | std::ios::binary);

    if (!input.is_open()) {
        throw "I can't open the file";
    }

    input.seekg(SIZE_OF_BMP_HEADER, std::ios::cur);
    input.seekg(DEFAULT_DATA_SIZE, std::ios::cur);  // skip DIB Header size
    int32_t width;
    int32_t height;
    FRead(input, width);
    FRead(input, height);

    Image result_image = Image(height, width);

    ReadImage(input, result_image);

    input.close();
    return result_image;
}