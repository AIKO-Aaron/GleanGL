#include "GleanGL.h"

#include "../../../../../Scripts/autogen_cpp.h"

__internalContext Glean::graphics::initGL(__internalWindow window) {
    __internalContext c = Glean::graphics::createGLContext(window);
    
    initGLean();
    
    printf("%p\n", glGetError);
    printf("%p\n", glGenBuffers);
    
    const char *vers = (const char*) glGetString(GL_VERSION);
    printf("[GLEAN][INFO] Loaded OpenGL Version: %s\n", vers);
    
    return c;
}
