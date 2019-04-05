#pragma once

#include <cmath>
#include <string>

#define PI 3.14159265358979323

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
                printf("Matrix (%d|%d):\n[\n\t", M, N);
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
            
            inline Matrix<M, N> operator*(float k) { Matrix<M, N> r = Matrix<M, N>(*this); for(int i = 0; i < N * M; i++) r[i] *= k; return r; }
            inline Matrix<M, N> operator/(float k) { Matrix<M, N> r = Matrix<M, N>(*this); for(int i = 0; i < N * M; i++) r[i] /= k; return r; }
            inline Matrix<M, N> operator*=(float k) { for(int i = 0; i < N * M; i++) mValues[i] *= k; return *this; }
            inline Matrix<M, N> operator/=(float k) { for(int i = 0; i < N * M; i++) mValues[i] /= k; return *this; }

            inline Matrix<M, N> operator+(Matrix<M, N> k) { Matrix<M, N> r = Matrix<M, N>(*this); for(int i = 0; i < N * M; i++) r[i] += k[i]; return r; }
            inline Matrix<M, N> operator-(Matrix<M, N> k) { Matrix<M, N> r = Matrix<M, N>(*this); for(int i = 0; i < N * M; i++) r[i] -= k[i]; return r; }
            inline Matrix<M, N> operator+=(Matrix<M, N> k) { for(int i = 0; i < N * M; i++) mValues[i] += k[i]; return *this; }
            inline Matrix<M, N> operator-=(Matrix<M, N> k) { for(int i = 0; i < N * M; i++) mValues[i] -= k[i]; return *this; }
            
            inline void operator=(Matrix<M, N> m) { for(int i = 0; i < M * N; i++) mValues[i] = m[i]; }
            
            inline void swapColumns(int c1, int c2) {
                for(int i = 0; i < N; i++) {
                    float tmp = mValues[c1 * N + i];
                    mValues[c1 * N + i] = mValues[c2 * N + i];
                    mValues[c2 * N + i] = tmp;
                }
            }
            
            inline void swapRows(int r1, int r2) {
                for(int i = 0; i < N; i++) {
                    float tmp = mValues[i * N + r1];
                    mValues[i * N + r1] = mValues[i * N + r2];
                    mValues[i * N + r2] = tmp;
                }
            }
            
            inline void subtractColumns(int c1, int c2) { // c1 -= c2
                for(int i = 0; i < N; i++) mValues[c1 * N + i] -= mValues[c2 * N + i];
            }
            
            inline void subtractMultipliedColumns(int c1, int c2, float factor) { // c1 -= f * c2
                for(int i = 0; i < N; i++) mValues[c1 * N + i] -= factor * mValues[c2 * N + i];
            }
            
            inline void multiplyColumn(int c, float factor) {
                for(int i = 0; i < N; i++) mValues[c * N + i] *= factor;
            }
            
            Matrix<M, M> inverse();
        };

        // Left handside stuff...
        template<int M, int N>
        static Matrix<M, N> operator*(const float k, Matrix<M, N> m) { return m * k; }
        
        // Other stuff that's long
        
        template<int M, int N>
        Matrix<M, M> Matrix<M, N>::inverse() {
            if(M != N) printf("[GLEAN][ERROR] Can't calculate inverse of non-square matrix!\n");
            
            Matrix<M, M> s(*this); // Copy of self
            Matrix<M, M> r; for(int i = 0; i < M; i++) r(i, i) = 1; // identity matrix
            
            for(int i = 0; i < M; i++) {
                float currentMax = abs(s[i * M + i]);
                int maxRow = i;
                for(int j = i + 1; j < M; j++) {
                    if(abs(s[j * M + i]) > currentMax) {
                        currentMax = abs(s[j * M + i]);
                        maxRow = j;
                    }
                }
                
                s.swapColumns(i, maxRow);
                r.swapColumns(i, maxRow);
                
                for(int j = i + 1; j < M; j++) {
                    float factor = s[j * M + i] / s[i * M + i];
                    if(factor != 0) {
                        s.subtractMultipliedColumns(j, i, factor);
                        r.subtractMultipliedColumns(j, i, factor);
                        
                        s(j, i) = 0; // Manually set it to 0
                    }
                }
            }
            
            // We got a upper right triangular matrix now...
            for(int i = M - 2; i >= 0; i--) { // Go from bottom to the top
                for(int j = i + 1; j < M; j++) {
                    float factor = s[j + i * M] / s[j + j * M];
                    if(factor != 0) {
                        s.subtractMultipliedColumns(i, j, factor);
                        r.subtractMultipliedColumns(i, j, factor);
                        
                        s(i, j) = 0;
                    }
                }
            }
            
            for(int i = 0; i < M; i++) {
                if(s[i * M + i] < 0) {
                    s.multiplyColumn(i, -1);
                    r.multiplyColumn(i, -1);
                }
            }
            
            return r;
        }
    }
}
