#include <cstring>

#include "shaderloader.h"

void ShaderLoader::setFilename(std::string filename) {
    _filename = filename;
}

const char* ShaderLoader::load() {
    std::string shader = "";
    if (_filename == "") {
        std::cerr << "ERROR::LOADING SHADER::NO_NAME" << std::endl;
        return nullptr;
    }
    std::ifstream shaderFile(_filename, std::ios::in);
    std::string ligne = "";
    if (shaderFile) {
        while (std::getline(shaderFile, ligne))
            shader += ligne+'\n';

        shaderFile.close();
        shader += '\0';
    } else {
        std::cerr << "ERROR::LOADING SHADER::CANNOT OPEN FILE" << std::endl;
        return nullptr;
    }
    char* out = new char[shader.size()];
    for (unsigned int i = 0; i < shader.size(); i++) {
        out[i] = shader[i];
    }
    std::cout << _filename << " Have been loaded." << std::endl << std::endl;
    return out;
}
