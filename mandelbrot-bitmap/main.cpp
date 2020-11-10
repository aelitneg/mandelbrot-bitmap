#include <cstdint>
#include <iostream>
#include <math.h>
#include <memory>

#include "Bitmap.h"
#include "Mandelbrot.h"

using namespace std;
using namespace mandelbrot_bitmap;

int main() {
	const int kWidth = 800;
	const int kHeight = 600;

	unique_ptr<int[]> histogram(new int[Mandelbrot::kMaxIterations]{ 0 });
	unique_ptr<int[]> fractal(new int[kWidth * kHeight]{ 0 });
	Bitmap bitmap(kWidth, kHeight);

	for (int y = 0; y < kHeight; y++) {
		for (int x = 0; x < kWidth; x++) {
			// Temporary Scaling Implementation
			double x_fractal = (x - kWidth / 2 - 200) * 2.0/kHeight;
			double y_fractal = (y - kHeight / 2) * 2.0/kHeight;

			int iterations = Mandelbrot::GetIterations(x_fractal, y_fractal);

			fractal[y * kWidth + x] = iterations;

			if (iterations != Mandelbrot::kMaxIterations) {
				histogram[iterations]++;
			}

			
		}
	}

	int total = 0;
	for (int i = 0; i < Mandelbrot::kMaxIterations; i++) {
		total += histogram[i];
	}

	for (int y = 0; y < kHeight; y++) {
		for (int x = 0; x < kWidth; x++) {
			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;

			int iterations = fractal[y * kWidth + x];

			if (iterations != Mandelbrot::kMaxIterations) {
				double hue = 0.0;
				for (int i = 0; i <= iterations; i++) {
					hue += ((double)histogram[i]) / total;
				}


				green = pow(255, hue);
			}

			bitmap.SetPixel(x, y, red, green, blue);
		}
	}

	bitmap.Write("test.bmp");

	return 0;
}