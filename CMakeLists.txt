cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        image.cpp
        image.h filters/filter.h filters/crop.h filters/crop.cpp filters/single_pixel_filter.h filters/single_pixel_filter.cpp filters/matrix_filter.h filters/matrix_filter.cpp filters/grayscale.h filters/grayscale.cpp filters/negative.cpp filters/negative.h filters/sharpening.h filters/sharpening.cpp filters/edge_detection.h filters/edge_detection.cpp filters/gaussian_blur.h filters/gaussian_blur.cpp filters/all_filters.h command_parser.h command_parser.cpp reader/reader.h reader/reader.cpp file_utilities/file_working_utilities.h file_utilities/file_working_utilities.cpp writer/writer.cpp writer/writer.h)
