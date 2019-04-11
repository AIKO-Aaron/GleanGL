//
//  Mac_Library.cpp
//  GleanGL
//
//  Created by Aaron Hodel on 01.04.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "../Universal/Platform.h"
#include <dlfcn.h>
#include "../Universal/OpenGL/GleanGL.h"

__internalLibrary Glean::library::openLibrary(const char *path) {
    return dlopen(path, RTLD_LAZY);
}

void* Glean::library::getFunctionAddress(__internalLibrary lib, const char *name) {
    return dlsym(lib, name);
}

void* Glean::library::getGLFunction(const char *name) {
    return getFunctionAddress(openLibrary("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"), name);
}

__internalContext Glean::graphics::createGLContext(__internalWindow iWind) {
    NSWindow *window = (__bridge NSWindow*) iWind;
    
    NSOpenGLPixelFormatAttribute attributes[] = {
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADepthSize, 32,
        NSOpenGLPFASampleBuffers, 2,
        NSOpenGLPFASamples, 4,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
        0
    };
    
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes: attributes];
    if(!pixelFormat) printf("[GLEAN][ERROR] Couldn't create PixelFormat...\n");
    NSOpenGLContext *context = [[NSOpenGLContext alloc] initWithFormat: pixelFormat shareContext: NULL];
    if(!context) printf("[GLEAN][ERROR] Couldn't create OpenGL context on MacOS\n");
    
    [context setView: [window contentView]];
    [context makeCurrentContext];
    
    return (__bridge __internalContext) context;
}

void Glean::graphics::swapBuffers(__internalContext context) {
    NSOpenGLContext *c = (__bridge NSOpenGLContext*) context;
    [c flushBuffer];
    glFlush();
}
