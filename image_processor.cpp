#include "filters/all_filters.h"
#include "command_parser.h"
#include "reader/reader.h"
#include "writer/writer.h"
#include <iostream>

void WriteReference() {
    std::cout
        << "Usage:\timage_processor INPUT_FILE OUTPUT_FILE [-FILTER1 PARAM1 ...] [-FILTER2 PARAM1 ...]"
        << std::endl;
    std::cout << std::endl;

    std::cout << "Apply several filters to bpm image" << std::endl;
    std::cout << std::endl;

    std::cout << "Filters:" << std::endl;
    std::cout << "  -crop WIDTH HEIGHT    Crop image" << std::endl;
    std::cout << "  -gs                   Apply grayscale" << std::endl;
    std::cout << "  -neg                  Apply negative" << std::endl;
    std::cout << "  -sharp                Apply sharpening" << std::endl;
    std::cout << "  -edge THRESHOLD       Apply edge detection" << std::endl;
    std::cout << "  -blur SIGMA           Apply gaussian blur" << std::endl;
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        WriteReference();
        return 1;
    }

    Parser parser(argc, argv);
    parser.Parse();

    Image image = file_handling::Read(parser.GetFileToRead());
    std::vector<std::unique_ptr<Filter>>& filters_ptr = parser.GetFilters();

    for (size_t i = 0; i < filters_ptr.size(); ++i) {
        image = filters_ptr[i]->Apply(image);
    }
    file_handling::Write(image, parser.GetFileToWrite());
    return 0;
}
