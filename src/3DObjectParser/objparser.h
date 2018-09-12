#ifndef OBJPARSER_H
#define OBJPARSER_H


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <opengl_stuff.h>

#include "../Materials/Imported3DModel.h"

class ObjParser {
public:
    static void parse(std::string fileName, std::vector<Material3DObject>* objects, bool comuputeNormals);
};

#endif
