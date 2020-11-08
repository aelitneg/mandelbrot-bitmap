#include "Bitmap.h"

using namespace mandelbrot_bitmap;

namespace mandelbrot_bitmap {
	Bitmap::Bitmap(int width, int height) : width_(width), height_(height), pixels_(new uint8_t[width * height * 3]{0}) {}

	void Bitmap::SetPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
		uint8_t* pixel = pixels_.get();

		pixel += (y*3) * width_ + (x*3);

		// Bitmap is Little-Endian
		pixel[0] = blue;
		pixel[1] = green;
		pixel[2] = red;
	}

	bool Bitmap::Write(string filename) {
		BitmapFileHeader file_header;
		BitmapInfoHeader info_header;

		file_header.file_size = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + (width_ * height_ * 3);
		file_header.data_offset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

		info_header.width = width_;
		info_header.height = height_;

		ofstream file;
		file.open(filename, ios::binary);
		
		if (!file) {
			return false;
		}

		file.write((char *)&file_header, sizeof(file_header));
		file.write((char *)&info_header, sizeof(info_header));
		file.write((char *)pixels_.get(), (width_ * height_ * 3));

		file.close();

		if (file.is_open()) {
			return false;
		}

		return true;
	}
}
