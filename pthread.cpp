#include "timer.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <pthread.h>
#include <random>

#define VERIFY 0

int n = 600;
int numThreads = 6;
std::vector<std::vector<double>> *matrix;
std::vector<std::vector<double>> *matrix_1;
std::vector<std::vector<double>> *L;
std::vector<std::vector<double>> *U;
std::vector<int> _pi;

struct ThreadData {
    int k, thread_id;
    ThreadData(int k, int thread_id) : k(k), thread_id(thread_id) {}
};

void *initialize(void *arg) {
    int thread_id = static_cast<int>(reinterpret_cast<long>(arg));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 10.0);

    for (int i = thread_id; i < n; i += numThreads) {
        for (int j = 0; j < n; ++j) {
            (*matrix)[i][j] = dis(gen) + 1;
            (*matrix_1)[i][j] = (*matrix)[i][j];
            (*U)[i][j] = 0;
            (*L)[i][j] = (j == i ? 1 : 0);
        }
    }
    return NULL;
}

void *update(void *arg) {
    struct ThreadData *data = (ThreadData *)arg;
    int k = data->k;
    int thread_id = data->thread_id;

    for (int i = k + 1 + thread_id; i < n; i += numThreads) {
        for (int j = k + 1; j < n; j++) {
            (*matrix)[i][j] -= (((*U)[k][j]) * ((*L)[i][k]));
        }
    }
    return NULL;
}

// SEQUENTIAL MATRIX PRINTING: Dont benchmark with this function running
void dbg(int n, std::vector<std::vector<double>> *matrix) {
    std::cout << std::fixed << std::setprecision(6);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << (*matrix)[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::vector<double>> *
matrixMultiply(const std::vector<std::vector<double>> *A,
               const std::vector<std::vector<double>> *B) {
    std::vector<std::vector<double>> *result =
        new std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                (*result)[i][j] += A->at(i)[k] * B->at(k)[j];
            }
        }
    }
    return result;
}

int main() {

    std::cout << "Number of Threads: " << numThreads << '\n';
    std::cout << "Matrix Dimention: " << n << '\n';

    matrix = new std::vector<std::vector<double>>(n, std::vector<double>(n));
    matrix_1 = new std::vector<std::vector<double>>(n, std::vector<double>(n));
    L = new std::vector<std::vector<double>>(n, std::vector<double>(n));
    U = new std::vector<std::vector<double>>(n, std::vector<double>(n));

    _pi = std::vector<int>(n);
    std::iota(_pi.begin(), _pi.end(), 0);

    pthread_t threads[numThreads];

    for (long i = 0; i < numThreads; ++i) {
        pthread_create(&threads[i], NULL, initialize, (void *)i);
    }

    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    {
        Timer t;

        for (int k = 0; k < n; k++) {
            double amax = 0;
            int kk(0);

            for (int i = k; i < n; i++) { // cache un-friendly! change later
                if (amax < fabs((*matrix)[i][k])) {
                    amax = fabs((*matrix)[i][k]);
                    kk = i;
                }
            }

            if (amax == 0) {
                std::cout << "Matrix Is Singular\n";
                std::cout << k << '\n';
                exit(0);
            }

            if (k != kk) {
                // swapping things here!
                std::swap(_pi[k], _pi[kk]);
                for (int j = 0; j < n; j++) {
                    std::swap((*matrix)[k][j], (*matrix)[kk][j]);
                }
                for (int j = 0; j < k; j++) {
                    std::swap((*L)[k][j], (*L)[kk][j]);
                }
            }

            (*U)[k][k] = (*matrix)[k][k];

            for (int i = k + 1; i < n; i++) {
                (*L)[i][k] = ((*matrix)[i][k]) / ((*U)[k][k]);
                (*U)[k][i] = (*matrix)[k][i];
            }

            std::vector<ThreadData> args;
            args.reserve(numThreads);

            for (int i = 0; i < numThreads; ++i) {
                args.push_back(ThreadData(k, i));
                pthread_create(&threads[i], NULL, update, (void *)&args[i]);
            }
            for (int i = 0; i < numThreads; ++i) {
                pthread_join(threads[i], NULL);
            }
        }
    }

    if (VERIFY == 1) {
        std::vector<std::vector<double>> *P =
            new std::vector<std::vector<double>>(n,
                                                 std::vector<double>(n, 0.0));
        for (int i = 0; i < n; i++) {
            (*P)[i][_pi[i]] = 1;
        }
        std::vector<std::vector<double>> *PA = matrixMultiply(P, matrix_1);
        std::vector<std::vector<double>> *LU = matrixMultiply(L, U);

        double norm = 0.0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                auto x = (*PA)[i][j] - (*LU)[i][j];
                norm += (x * x);
            }
        }

        norm = std::sqrt(norm);
        std::cout << "The error norm is: " << norm << '\n';

        delete P;
        delete LU;
        delete PA;
    }

    delete matrix;
    delete matrix_1;
    delete L;
    delete U;
}