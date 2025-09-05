#include <iostream>
#include <eigen3/Eigen/Dense>

float computeConditionNumber(const Eigen::MatrixXf& eigenMatrix) {
    Eigen::JacobiSVD<Eigen::MatrixXf> svd(eigenMatrix);
    
    float maxSingularValue = svd.singularValues()(0);
    float minSingularValue = svd.singularValues()(svd.singularValues().size() - 1);

    if (minSingularValue == 0) {
        throw std::runtime_error("Matrix is singular (condition number is infinite)");
    }
    return maxSingularValue / minSingularValue;
}

Eigen::VectorXf solveLinearSystem(const Eigen::MatrixXf& eigenA, const Eigen::VectorXf& eigenB) {

    Eigen::VectorXf x = eigenA.colPivHouseholderQr().solve(eigenB);

    return x;
}

float computeRelativeResidual(const Eigen::MatrixXf& eigenA, const Eigen::VectorXf& eigenB, const Eigen::VectorXf& eigenX) {
    Eigen::VectorXf residual = eigenA * eigenX - eigenB;

    float residualNorm = residual.norm();
    float bNorm = eigenB.norm();

    if (bNorm == 0.0f) {
        throw std::runtime_error("||b|| is zero (division by zero)");
    }

    return residualNorm / bNorm;
}

