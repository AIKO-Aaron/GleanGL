#pragma once

#include "Matrix.h"
#include <cmath>

namespace Glean {
    namespace math {
        
        template <int M>
        class Vector : public Matrix<M, 1> {
        private:
            
        public:
            Vector() : Matrix<M, 1>() {}
            Vector(float value) : Matrix<M, 1>(value) {}
            Vector(float *values) : Matrix<M, 1>(values) {}
            
            template<int N>
            Vector(Vector<N> v) : Matrix<M, 1>() { for(int i = 0; i < (M < N ? M : N); i++) this->mValues[i] = v[i]; }
            Vector(Matrix<M, 1> m) : Matrix<M, 1>() { for(int i = 0; i < M; i++) this->mValues[i] = m[i]; }
            
            inline void operator=(Vector<M> other) { for(int i = 0; i < M; i++) this->mValues[i] = other[i]; }
            
            inline float dot(Vector<M> other) { float p = 0; for(int i = 0; i < M; i++) p += other[i] * this->mValues[i]; return p; }

            inline float angleBetween(Vector<M> other) { return acos(dot(other) / (other.length() * length())); }
            
            inline float length() { float l = 0; for(int i = 0; i < M; i++) l += this->mValues[i] * this->mValues[i]; return sqrt(l); }
            inline float lengthSquared() { float l = 0; for(int i = 0; i < M; i++) l += this->mValues[i] * this->mValues[i]; return l; }
        };
        
        template<int M>
        static Vector<M> operator*(Matrix<M, M> m, Vector<M> v) {
            Matrix<M, 1> m1 = m.operator*(v); // avoid recursion
            Vector<M> v1 = m1;
            return v1;
        }
        
        static Vector<3> cross(Vector<3> a, Vector<3> b) {
            Vector<3> r;
            r[0] = a[1] * b[2] - a[2] * b[1];
            r[1] = a[2] * b[0] - a[0] * b[2];
            r[2] = a[0] * b[1] - a[1] * b[0];
            return r;
        }
        
        static Vector<2> createVector(float x, float y) {
            Vector<2> r = Vector<2>();
            r[0] = x;
            r[1] = y;
            return r;
        }
        
        static Vector<3> createVector(float x, float y, float z) {
            Vector<3> r = Vector<3>();
            r[0] = x;
            r[1] = y;
            r[2] = z;
            return r;
        }
        
        static Vector<4> createVector(float x, float y, float z, float w) {
            Vector<4> r = Vector<4>();
            r[0] = x;
            r[1] = y;
            r[2] = z;
            r[3] = w;
            return r;
        }
        
    }
}
