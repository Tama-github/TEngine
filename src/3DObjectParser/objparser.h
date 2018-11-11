#ifndef OBJPARSER_H
#define OBJPARSER_H


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <opengl_stuff.h>

#include "../Materials/Imported3DModel.h"
#include "../Materials/composed3dobject.h"

class ObjParser {
public:
    static void parse(std::string fileName, std::vector<Composed3DObject>* objects, bool comuputeNormals);
};

#endif
