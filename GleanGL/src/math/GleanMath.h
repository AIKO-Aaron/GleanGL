#pragma once

#include "Matrix.h"
#include "Vector.h"

namespace Glean {
    namespace math {
        
        template<int N>
        static Matrix<N, N> identity() {
            Matrix<N, N> r;
            for(int i = 0; i < N; i++) r(i, i) = 1;
            return r;
        }
        
        static Matrix<4, 4> rotate_x(float angle) {
            Matrix<4, 4> r;
            
            r(0, 0) = 1;
            r(1, 1) = cos(angle);
            r(2, 1) = sin(angle);
            r(2, 2) = cos(angle);
            r(1, 2) = -sin(angle);
            r(3, 3) = 1;
            
            return r;
        }
        
        static Matrix<4, 4> rotate_y(float angle) {
            Matrix<4, 4> r;
            
            r(0, 0) = cos(angle);
            r(0, 2) = sin(angle);
            r(1, 1) = 1;
            r(2, 0) = -sin(angle);
            r(2, 2) = cos(angle);
            r(3, 3) = 1;
                        
            return r;
        }
        
        static Matrix<4, 4> rotate_z(float angle) {
            Matrix<4, 4> r = identity<4>();

            r(0, 0) = cos(angle);
            r(0, 1) = sin(angle);
            r(1, 0) = -sin(angle);
            r(1, 1) = cos(angle);
            r(2, 2) = 1;
            r(3, 3) = 1;
            
            return r;
        }
    }
}
