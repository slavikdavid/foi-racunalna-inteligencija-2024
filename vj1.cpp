#include <chrono>
#include <cmath>
#include <csignal>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

bool interrupted = false;

void signalHandler(int signum) {
    std::cout << "\033[1;31mPrekid (" << signum << ") zaprimljen.\033[0m\n";
    std::cout << "Gasim program...\n";
    interrupted = true;
}

double funkcijaA(double x) {
    double fx = 0.2 * (x - 2.0) * sin(7.0 * x - 15.0) + 1;
    if (fx >= 1.0)
        fx = cos(2.0 / (pow(x - 6.0, 2.0) + 1.0)) + 0.7;
    return fx;
}

int main() {
    signal(SIGINT, signalHandler);
    signal(SIGTSTP, signalHandler);
    signal(SIGQUIT, signalHandler);

    std::random_device rd;
    unsigned long long seed = rd();

    std::mt19937_64 rng(seed);

    double Xlb = 2.0;
    double Xub = 6.0;
    double xNB;
    double fxNB = INFINITY;
    unsigned swarmSize = 10;

    std::vector<double> xPB;
    std::vector<double> x;
    std::vector<double> v;

    long nIterations = 50;
    double w = 0.8;
    double C1 = 2;
    double C2 = 1.6;

    x.resize(swarmSize);
    v.resize(swarmSize);
    xPB.resize(swarmSize);
    plt::ion();
    plt::xlim(-10, 10);
    plt::ylim(0, 3);
    plt::xlabel("x");
    plt::ylabel("f(x)");
    plt::title("Optimizacija rojeva čestica");

    for (long iter = 0; iter < nIterations && !interrupted; iter++) {
        plt::clf();

        std::vector<double> X, Y;
        for (double i = Xlb; i <= Xub; i += 0.01) {
            X.push_back(i);
            Y.push_back(funkcijaA(i));
        }
        plt::plot(X, Y, "b-");

        std::vector<double> particleX, particleY;
        for (unsigned i = 0; i < swarmSize; i++) {
            particleX.push_back(x[i]);
            particleY.push_back(funkcijaA(x[i]));
        }
        plt::plot(particleX, particleY, "ro");

        plt::pause(0.05);

        std::cout << "\033[1;33mIteracija " << iter + 1 << "/" << nIterations << ":\033[0m\n";
        for (unsigned i = 0; i < swarmSize; i++) {
            std::cout << "   \033[1;35mČestica " << i + 1 << ":\033[0m (" << x[i] << ", " << funkcijaA(x[i]) << ")\n";
        }

        for (unsigned i = 0; i < swarmSize; i++) {
            v[i] = w * v[i] + C1 * (xPB[i] - x[i]) + C2 * (xNB - x[i]);
            x[i] = x[i] + v[i];

            if (x[i] > Xub) {
                x[i] = Xub;
            }
            if (x[i] < Xlb) {
                x[i] = Xlb;
            }

            if (funkcijaA(x[i]) < funkcijaA(xPB[i])) {
                xPB[i] = x[i];
                if (funkcijaA(xPB[i]) < fxNB) {
                    xNB = xPB[i];
                    fxNB = funkcijaA(xNB);
                }
            }
        }
    }

    std::cout << "\033[32mKonačno rješenje:\033[0m (\033[33m" << xNB << ", " << fxNB << "\033[0m)\n";

    plt::show();
    return 0;
}
