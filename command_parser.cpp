#include "command_parser.h"
#include "filters/all_filters.h"

Parser::Parser(int argc, const char* argv[]) : argc_(argc), argv_(argv) {
    commands_["-crop"] = [&]() { ParseCrop(); };
    commands_["-gs"] = [&]() { ParseGs(); };
    commands_["-neg"] = [&]() { ParseNeg(); };
    commands_["-sharp"] = [&]() { ParseSharp(); };
    commands_["-edge"] = [&]() { ParseEdge(); };
    commands_["-blur"] = [&]() { ParseBlur(); };
}

void Parser::Parse() {
    if (argc_ < 3) {
        throw std::invalid_argument("usage: <file1> <file2> ...");
    }
    file_to_read_ = argv_[1];
    file_to_write_ = argv_[2];
    pos_ += 2;
    while (pos_ < argc_) {
        Iterate();
    }
}

void Parser::Iterate() {
    CommandName command_name = argv_[pos_];

    auto it = commands_.find(command_name);
    if (it == commands_.end()) {
        throw std::invalid_argument("need filter name, get " + std::string(argv_[pos_]));
    }
    it->second();
    ++pos_;
}

void Parser::ParseCrop() {
    pos_ += 2;
    if (pos_ > argc_) {
        throw std::out_of_range("usage: -crop <width> <height>");
    }
    int32_t width = 0;
    int32_t height = 0;
    try {
        width = std::stoi(argv_[pos_ - 1]);
        height = std::stoi(argv_[pos_]);
        if (width <= 0 || height <= 0) {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument("Crop filter arguments: width, height must be positive integer");
    }
    filters_.push_back(std::make_unique<Crop>(height, width));
}

void Parser::ParseGs() {
    filters_.push_back(std::make_unique<GrayScale>());
}

void Parser::ParseNeg() {
    filters_.push_back(std::make_unique<Negative>());
}

void Parser::ParseSharp() {
    filters_.push_back(std::make_unique<Sharpening>());
}

void Parser::ParseEdge() {
    ++pos_;
    if (pos_ > argc_) {
        throw std::out_of_range("usage: -edge <threshold>");
    }
    double threshold = 0;
    try {
        threshold = std::stod(argv_[pos_]);
        if (threshold < 0 || 1 < threshold) {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument("Edge filter arguments: threshold must be real from 0 to 1");
    }
    filters_.push_back(std::make_unique<EdgeDetection>(threshold));
}

void Parser::ParseBlur() {
    ++pos_;
    if (pos_ > argc_) {
        throw std::out_of_range("usage: -blur <sigma>");
    }
    double sigma;
    try {
        sigma = std::stod(argv_[pos_]);
    } catch (const std::exception& e) {
        throw std::invalid_argument("Blur filter arguments: sigma must be real");
    }
    filters_.push_back(std::make_unique<GaussianBlur>(sigma));
}

std::string Parser::GetFileToRead() const {
    return file_to_read_;
}

std::string Parser::GetFileToWrite() const {
    return file_to_write_;
}

std::vector<std::unique_ptr<Filter>>& Parser::GetFilters() {
    return filters_;
}
