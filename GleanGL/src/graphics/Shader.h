#pragma once

#include "Universal/OpenGL/GleanGL.h"
#include "../math/GleanMath.h"
#include "../util/FileUtil.h"
#include <string>

namespace Glean {
	namespace graphics {

		class Shader {
		private:
			GLuint shaderID = -1;

		public:
			Shader(const char *vertSrc, const char *fragSrc);

			inline void bind() { glUseProgram(shaderID); }
            inline void uniform(const char *name, float value) { glUniform1f(glGetUniformLocation(shaderID, name), value); }
            inline void uniform(const char *name, float v1, float v2) { glUniform2f(glGetUniformLocation(shaderID, name), v1, v2); }
            inline void uniform(const char *name, float v1, float v2, float v3) { glUniform3f(glGetUniformLocation(shaderID, name), v1, v2, v3); }
            inline void uniform(const char *name, float v1, float v2, float v3, float v4) { glUniform4f(glGetUniformLocation(shaderID, name), v1, v2, v3, v4); }
            
            inline void uniform(const char *name, Glean::math::Vector<2> v) { glUniform2f(glGetUniformLocation(shaderID, name), v[0], v[1]); }
            inline void uniform(const char *name, Glean::math::Vector<3> v) { glUniform3f(glGetUniformLocation(shaderID, name), v[0], v[1], v[2]); }
            inline void uniform(const char *name, Glean::math::Vector<4> v) { glUniform4f(glGetUniformLocation(shaderID, name), v[0], v[1], v[2], v[3]); }

            inline void uniform(const char *name, Glean::math::Matrix<4, 4> v) { glUniformMatrix4fv(glGetUniformLocation(shaderID, name), 1, GL_TRUE, &v[0]); }
        };

		extern Shader* loadShaderRecursive(const char *vertPath, const char *fragPath, int depth = 9);
	}
}
