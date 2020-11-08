#pragma once

#include <complex>

using namespace std;

namespace mandelbrot_bitmap {
	class Mandelbrot
	{
	public:
		static const int kMaxIterations = 1000;

		static int GetIterations(double x, double y);
	};
}

