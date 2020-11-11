#pragma once

#include <cstdint>
#include <string>
#include <math.h>
#include <memory>


#include "Bitmap.h"
#include "Mandelbrot.h"
#include "Zoom.h"
#include "ZoomList.h"

using namespace std;

namespace mandelbrot_bitmap {
	class FractalCreator
	{
	private:
		int width_{ 0 };
		int height_{ 0 };
		unique_ptr<int[]> histogram_;
		unique_ptr<int[]> fractal_;
		Bitmap bitmap_;
		ZoomList zoomList_;
		int total_{ 0 };
	public:
		FractalCreator(int width, int height);

		void CalculateIterations();
		void CalculateTotalIterations();

		void DrawFractal();

		void WriteBitmap(string filename);
		void AddZoom(const Zoom& zoom);
	};
}

