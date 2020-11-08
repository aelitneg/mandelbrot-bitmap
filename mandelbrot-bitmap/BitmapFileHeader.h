#pragma once

#include <cstdint>

using namespace std;

#pragma pack(2)

namespace mandelbrot_bitmap {
	struct BitmapFileHeader {
		char header[2]{ 'B', 'M' };
		int32_t file_size;
		int32_t reserved{};
		int32_t data_offset;
	};
}