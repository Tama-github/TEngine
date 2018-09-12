#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <string>
#include <iostream>
#include <fstream>

class ShaderLoader {
public:
    explicit ShaderLoader(std::string filename) :
        _filename(filename)
    {}
    void setFilename(std::string filename);
    const char* load();

private:
    std::string _filename;
};

#endif
