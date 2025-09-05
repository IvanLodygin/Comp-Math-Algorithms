#include <iostream>
#include <cmath>

double func(double x){
    return pow(x, 2) - pow(x, 3) - 1/(4 + pow(x, 2));
}

double roundValue(double x, double delta){
    return round(x / delta) * delta;
}

double bisection(double a, double b, double eps, int& iterationsCount){
    double e = (a + b) / 2;
    if (func(a) * func(b) < 0){
        if (func(e) == 0 || (b - a) < 2 * eps){
            return roundValue(e, eps);
        }
        else if (func(e) * func(a) < 0){
            return bisection(a, e, eps, ++iterationsCount);
        }
        else{
            return bisection(e, b, eps, ++iterationsCount);
        }
        
    }
    else{
        std::cout << "Неверно заданный интервал!" << std::endl;
        exit(1);
    }
}

double errorFunc(double x, double delta) {
    return func(roundValue(x, delta));
}

double errorCheckInBisection(double a, double b, double eps, int& iterationsCount, double delta) {
    double e = (a + b) / 2;
    if (errorFunc(a, delta) * errorFunc(b, delta) < 0) {
        if (errorFunc(e, delta) == 0 || (b - a) < 2 * eps) {
            return roundValue(e, eps);
        }
        else if (errorFunc(e, delta) * errorFunc(a, delta) < 0) {
            return errorCheckInBisection(a, e, eps, ++iterationsCount, delta);
        }
        else {
            return errorCheckInBisection(e, b, eps, ++iterationsCount, delta);
        }
    }
    else {
        std::cout << "Неверно заданный интервал!" << std::endl;
        exit(1);
    }
}

int main(){
    int counter = 0;
    double eps;
    std::cin >> eps;
    std::cout << bisection(-0.5, 0, eps, counter) << std::endl;
    return 0;
}