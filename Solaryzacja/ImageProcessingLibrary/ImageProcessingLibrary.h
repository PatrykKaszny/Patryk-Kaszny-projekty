#pragma once

#include <cstdint>

extern "C" __declspec(dllexport) void ConvertToGrayscale(unsigned char* pixelData, int width, int height, int stride, int numThreads);
