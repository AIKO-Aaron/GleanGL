#pragma once

#include <stdio.h>
#include <fstream>

namespace Glean {
    namespace util {
        
        typedef struct FileData {
            const char *path;
            char *data;
            long length;
        } FileData;
        
        extern FileData readFile(const char *path);
        extern FileData readWithProcessing(const char *path, int depth);
        
    }
}
