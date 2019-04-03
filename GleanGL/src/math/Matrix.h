#pragma once

#include <string>

namespace Glean {
    namespace math {
        
        template<int M, int N>
        class Matrix {
        protected:
            float *mValues = nullptr;
            
        public:
            Matrix() {
                mValues = (float*) malloc(sizeof(float) * N * M);
                for(int i = 0; i < N * M; i++) mValues[i] = 0;
            }
            
            Matrix(float value) {
                mValues = (float*) malloc(sizeof(float) * N * M);
                for(int i = 0; i < N * M; i++) mValues[i] = value;
            }
            
            Matrix(float *values) {
                mValues = (float*) malloc(sizeof(float) * N * M);
                for(int i = 0; i < N * M; i++) mValues[i] = values[i];
            }
            
            Matrix(const Matrix& m) {
                mValues = (float*) malloc(sizeof(float) * N * M);
                for(int i = 0; i < N * M; i++) mValues[i] = m.mValues[i];
            }
            
            ~Matrix() {
                free((void*) mValues);
            }
            
            inline void print() {
                printf("Matrix:\n[\n\t");
                for(int i = 0; i < M; i++) {
                    for(int j = 0; j < N; j++) {
                        printf("%.08f%s", mValues[i * N + j], j == N-1 ? "" : ", ");
                    }
                    printf("\n%s", i == M - 1 ? "" : "\t");
                }
                printf("]\n");
            }
            
            inline float& operator[](int i) { return mValues[i]; }
            inline float& operator()(int m, int n) { return mValues[m * N + n]; }
            
            template<int T>
            inline Matrix<M, T> operator*(Matrix<N, T> other) {
                Matrix<M, T> ret;
                for(int i = 0; i < M * T; i++) for(int j = 0; j < N; j++) ret[i] += mValues[((int) (i / T)) * N + j] * other[(i % T) + j * T];
                return ret;
            }
            
        };
        
    }
}
