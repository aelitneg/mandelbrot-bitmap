#pragma once

#include <assert.h>
#include <cstdint>
#include <string>
#include <math.h>
#include <memory>
#include <vector>

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "RGB.h"
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

		vector<int> ranges_;
		vector<RGB> colors_;
		vector<int> range_totals_;

		bool got_first_range_{false};

	private:
		void CalculateIterations();
		void CalculateTotalIterations();
		void CalculateRangeTotals();
		int GetRange(int iterations) const;

		void DrawFractal();

		void WriteBitmap(string filename);

	public: 
		FractalCreator(int width, int height);

		void Run(string filename);

		void AddRange(double rangeEnd, const RGB& rgb);
		void AddZoom(const Zoom& zoom);
	};
}

