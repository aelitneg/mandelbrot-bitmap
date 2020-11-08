#include <cstdint>
#include <iostream>

#include "Bitmap.h"
#include "Mandelbrot.h"

using namespace std;
using namespace mandelbrot_bitmap;

int main() {
	const int kWidth = 800;
	const int kHeight = 600;
	
	// Temporary Scaling Limits
	double max = -999999;
	double min = 999999;

	Bitmap bitmap(kWidth, kHeight);

	for (int y = 0; y < kHeight; y++) {
		for (int x = 0; x < kWidth; x++) {
			// Temporary Scaling Implementation
			double x_fractal = (x - kWidth / 2) * 2.0/kWidth;
			double y_fractal = (y - kHeight / 2) * 2.0/kHeight;

			int iterations = Mandelbrot::GetIterations(x_fractal, y_fractal);

			uint8_t red = (uint8_t)((double)iterations / Mandelbrot::kMaxIterations * 256);
			
			bitmap.SetPixel(x, y, red, 0, 0);
		}
	}

	bitmap.Write("test.bmp");

	return 0;
}