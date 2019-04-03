#pragma once

#include "Universal/OpenGL/GleanGL.h"
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
		};

		extern Shader* loadShaderRecursive(const char *vertPath, const char *fragPath, int depth = 9);
	}
}
