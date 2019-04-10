#include "GleanGL.h"

#include "../../../../../../Scripts/autogen_cpp.h"

__internalContext Glean::graphics::initGL(__internalWindow window) {
    __internalContext c = Glean::graphics::createGLContext(window);
    
    initGLean();
    
    glEnable(GL_DEPTH_TEST);
    
    const char *vers = (const char*) glGetString(GL_VERSION);
    printf("[GLEAN][INFO] Loaded OpenGL Version: %s\n", vers);
    
#if defined(_DEBUG) or defined(DEBUG)
    printf("[GLEAN][DEBUG] OpenGL Extensions: \n");
    int i = 0;
    const unsigned char* name = glGetStringi(GL_EXTENSIONS, i);
    while(name) {
        printf("[GLEAN][DEBUG] \t\t%s\n", name);
        name = glGetStringi(GL_EXTENSIONS, i++);
    }
    glGetError();
#endif
    
    return c;
}
