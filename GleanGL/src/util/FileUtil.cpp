#include "FileUtil.h"

using namespace Glean::util;

FileData Glean::util::readFile(const char *path) {
    FILE *f;
    
#ifdef __APPLE__
    f = fopen(path, "rb");
#elif defined(_WIN32)
    fopen_s(&f, path, "rb");
#else
    
#endif
    
    FileData fd;
    fd.path = path;
    
    if(f == nullptr) {
        printf("[GLEAN][ERROR] Could not open file: %s\n", path);
        return fd;
    }
    
    fseek(f, 0, SEEK_END);
    fd.length = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    fd.data = (char*) malloc(fd.length + 1);
    fd.data[fd.length] = 0;
    
    size_t read = fread(fd.data, 1, fd.length, f);
    if(read != fd.length) {
        printf("[GLEAN][ERROR] Could not read entire file: %s\n", path);
        fclose(f);
        return fd;
    }
    
    fclose(f);

    return fd;
}

FileData Glean::util::readWithProcessing(const char *filePath, int depth) {
    FileData fd = readFile(filePath);
    if(!depth) return fd; // Don't load more than 10 files recursively, exit condition
    
    printf("[GLEAN][INFO] Loading File: %s\n", filePath);
    
    int s = -1;
    while(s < fd.length) {
        if(s == -1 || fd.data[s++] == '\n') { // newline char
			if (s < 0) ++s;
            while(fd.data[s] == ' ' || fd.data[s] == '\t') ++s;
            if(fd.data[s] == '#') { // We're in a preprocessor statement
                int len = 0; // Length of directive
                int start = s; // Start at current offset in file
                while(fd.data[s++] != '\n' && s < fd.length) ++len; // Search for next newline
                //len--;
                //s--;
                
                // Load the preprocessor directive into str
                char *str = (char*) malloc(len + 1);
                memcpy(str, fd.data + start, len);
                str[len] = 0;
                // Check if is a not known directive (Filesystem, ...)
                if(!memcmp(str, "#include ", 9)) {
                    int i = 9;
                    while(str[i++] != '"') ; // Search for beginning of string
                    int j = i + 1;
                    while(str[j++] != '"') ; // Search for end of string
                    
                    char *filename = (char*) malloc(j - i);
                    memcpy(filename, str + i, j - i);
                    filename[j - i - 1] = 0;
                    
                    FileData loadedFile = readWithProcessing(filename, depth - 1);
                    
                    // data + start until j+1
                    uint64_t newsize = fd.length - s + start + loadedFile.length;
                    char *newFile = (char*) malloc((size_t) newsize + 1);
                    memcpy(newFile, fd.data, start); // Copy start of current file
                    memcpy(newFile + start, loadedFile.data, (size_t) loadedFile.length); // Copy the new loaded file to the place it should go
                    memcpy(newFile + start + loadedFile.length, fd.data + s, (size_t) fd.length - s + 1); // Copy the rest of our file
                    newFile[newsize] = 0;
                    
                    free(loadedFile.data); // Free newly loaded file
                    free(filename); // Free the filename string
                    free(fd.data); // Free the datas of the file, as we have a new one
                    fd.data = newFile; // Set the pointer in fd to the new one
                    fd.length = newsize; // Update the size
                    
                    s = start - 1; // Go back to the start of the line
                }
                
                --s;
                free(str);
            }
        }
    }
    
    return fd;
}
