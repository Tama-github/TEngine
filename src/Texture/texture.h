#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture {
public:
    Texture();

    unsigned int _id;
    std::string _type;
    std::string _path;
};

#endif // TEXTURE_H
