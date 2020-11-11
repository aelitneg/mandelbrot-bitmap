#include "FractalCreator.h"

namespace mandelbrot_bitmap {
	FractalCreator::FractalCreator(int width, int height) : width_(width),
		height_(height),
		histogram_(new int[Mandelbrot::kMaxIterations]{ 0 }),
		fractal_(new int[width_ * height_]{ 0 }),
		bitmap_(width_, height_),
		zoomList_(width_, height_) {

		zoomList_.Add(Zoom(width_ / 2, height_ / 2, 4.0 / width_));
	}

	void FractalCreator::CalculateIterations() {
		for (int y = 0; y < height_; y++) {
			for (int x = 0; x < width_; x++) {
				pair <double, double> coordinates = zoomList_.DoZoom(x, y);

				int iterations = Mandelbrot::GetIterations(coordinates.first, coordinates.second);

				fractal_[y * width_ + x] = iterations;

				if (iterations != Mandelbrot::kMaxIterations) {
					histogram_[iterations]++;
				}
			}
		}
	}

	void FractalCreator::CalculateTotalIterations() {
		for (int i = 0; i < Mandelbrot::kMaxIterations; i++) {
			total_ += histogram_[i];
		}
	}

	void FractalCreator::DrawFractal() {
		for (int y = 0; y < height_; y++) {
			for (int x = 0; x < width_; x++) {
				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;

				int iterations = fractal_[y * width_ + x];

				if (iterations != Mandelbrot::kMaxIterations) {
					double hue = 0.0;
					for (int i = 0; i <= iterations; i++) {
						hue += ((double)histogram_[i]) / total_;
					}

					green = pow(255, hue);
				}

				bitmap_.SetPixel(x, y, red, green, blue);
			}
		}
	}

	void FractalCreator::WriteBitmap(string filename) {
		bitmap_.Write(filename);
	}

	void FractalCreator::AddZoom(const Zoom& zoom) {
		zoomList_.Add(zoom);
	}
}
