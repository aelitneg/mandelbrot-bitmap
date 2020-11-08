#pragma once

#include <cstdint>
#include <fstream>
#include <memory>
#include <string>

#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

using namespace std;

namespace mandelbrot_bitmap {
	class Bitmap {
	private:
		int width_{ 0 };
		int height_{ 0 };
		unique_ptr<uint8_t[]> pixels_{ nullptr };

	public:
		Bitmap(int width, int height);

		void SetPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
		bool Write(string filename);
	};
}