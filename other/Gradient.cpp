#include "Gradient.h"

double gradient(double (*func)(double, double), double& x, double& y) {
    {
        constexpr double h = 1e-5;
        constexpr double tolerance = 1e-6;
        constexpr int maxIterations = 10000;

        constexpr double minBound = -5.0;
        constexpr double maxBound = 5.0;

        for (int i = 0; i < maxIterations; ++i) {
            double gx = (func(x + h, y) - func(x - h, y)) / (2.0 * h);
            double gy = (func(x, y + h) - func(x, y - h)) / (2.0 * h);

            double gradSquared = gx * gx + gy * gy;

            //stop criteira
            if (gradSquared < tolerance * tolerance) break;
                

            double alpha = 0.1;
            double current = func(x, y);

            bool accepted = false;

            while (alpha > 1e-12) {

                double nx = std::clamp(
                    x - alpha * gx, minBound, maxBound
                );

                double ny = std::clamp(
                    y - alpha * gy, minBound, maxBound
                );

                //
                double next = func(nx, ny);

                if (next <= current - 1e-4 * alpha * gradSquared) {
                    x = nx;
                    y = ny;
                    accepted = true;
                    break;
                }

                alpha *= 0.5;
            }
            if (!accepted)
                break;
        }
        return func(x, y);
    }
}