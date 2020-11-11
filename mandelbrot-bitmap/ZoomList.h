#pragma once

#include <vector>
#include <utility>
#include "Zoom.h"

using namespace std;

namespace mandelbrot_bitmap {
	class ZoomList
	{
	private:
		int width_{ 0 };
		int height_{ 0 };
		double x_center_{ 0 };
		double y_center_{ 0 };
		double scale_{ 1.0 };
		vector<Zoom> zooms_;

	public:
		ZoomList(int width, int height);

		void Add(const Zoom &zoom);
		pair<double, double> DoZoom(int x, int y);
	};
}

