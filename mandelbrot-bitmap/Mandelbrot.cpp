#include "Mandelbrot.h"

using namespace mandelbrot_bitmap;

int Mandelbrot::GetIterations(double x, double y) {
	complex<double> z = 0;
	complex<double> c(x, y);

	int iterations = 0;
	while (iterations < kMaxIterations) {
		z = z * z + c;

		if (abs(z) > 2) {
			break;
		}

		iterations++;
	}

	return iterations;
}
