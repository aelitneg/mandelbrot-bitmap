#include "ZoomList.h"

namespace mandelbrot_bitmap {
	ZoomList::ZoomList(int width, int height) : width_(width), height_(height) {}

	void ZoomList::Add(const Zoom& zoom) {
		x_center_ += (zoom.x - width_ / 2) * scale_;
		y_center_ += (zoom.y - height_ / 2) * scale_;

		scale_ *= zoom.scale;

		zooms_.push_back(zoom);
	}

	pair<double, double> ZoomList::DoZoom(int x, int y) {
		double x_fractal = (x - width_ / 2) * scale_ + x_center_;
		double y_fractal = (y - height_ / 2) * scale_ + y_center_;


		return pair<double, double>{x_fractal, y_fractal};
	}
}
