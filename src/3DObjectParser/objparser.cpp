#include "objparser.h"

std::string replaceDash(std::string s) {
    std::string ret="";
    for(unsigned int i=0;i<s.size();i++) {
        if(s[i]=='/')
            ret+=' ';
        else
            ret+=s[i];
    }
    return ret;
}

std::vector<float> splitToGetValues(std::string line) {
    std::vector<float> res;
    std::vector<std::string> tempVec;
    char sep = ' ';
    for (size_t p=0, q=0; p!=line.npos; p=q)
        tempVec.emplace_back(line.substr(p+(p!=0), (q=line.find(sep, p+1))-p-(p!=0)));

    tempVec.erase(tempVec.begin());
    for (auto e : tempVec) {
        std::stringstream ss;
        float f;
        ss.str(e);
        ss >> f;
        res.emplace_back(f);
    }
    return res;
}

void ObjParser::parse(std::string fileName, std::vector<Material3DObject>* objects, bool comuputeNormals)
{
    if (fileName == "") {
        std::cerr << "ERROR::LOADING SHADER::NO_NAME" << std::endl;
    }

    std::ifstream obj(fileName, std::ios::in);
    std::string line = "";

    std::vector<glm::vec3> v;
    std::vector<glm::vec3> n;
    std::vector<std::vector<GLuint>> t;


    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLuint> indices;

    GLfloat fmax = 0;

    std::vector<float> temp;

    if (obj) {
        while (std::getline(obj, line)) {
            switch (line[0]) {
                case 'v':
                    switch (line[1]) {
                        case ' ':
                            temp = splitToGetValues(line);
                            v.push_back(glm::vec3(temp[0], temp[1], temp[2]));
                            fmax = std::max(std::max(std::max(fmax,temp[0]),temp[1]),temp[2]);
                            break;
                        case 'n':
                            char n1[255],n2[255],n3[255];
                            sscanf(line.c_str(),"vn %s %s %s",n1,n2,n3);
                            n.push_back(glm::vec3((GLfloat) strtod(n1,nullptr), (GLfloat) strtod(n2,nullptr), (GLfloat) strtod(n3,nullptr)));
                            break;
                    }
                    break;
                case 'f':
                    line = replaceDash(line);
                    char v1[255],v2[255],v3[255];
                    char vn1[255],vn2[255],vn3[255];
                    sscanf(line.c_str(),"f %s  %s %s  %s %s  %s",v1,vn1,v2,vn2,v3,vn3);
                    GLuint uiv1 = (GLuint) strtod(v1,nullptr) - 1 ;
                    GLuint uiv2 = (GLuint) strtod(v2,nullptr) - 1;
                    GLuint uiv3 = (GLuint) strtod(v3,nullptr) - 1;
                    GLuint uivn1 = (GLuint) strtod(vn1,nullptr) - 1;
                    GLuint uivn2 = (GLuint) strtod(vn2,nullptr) - 1;
                    GLuint uivn3 = (GLuint) strtod(vn3,nullptr) - 1;

                    std::vector<GLuint> a;
                    a.push_back(uiv1);
                    a.push_back(uivn1);
                    std::vector<GLuint> b;
                    b.push_back(uiv2);
                    b.push_back(uivn2);
                    std::vector<GLuint> c;
                    c.push_back(uiv3);
                    c.push_back(uivn3);

                    t.push_back(a);
                    t.push_back(b);
                    t.push_back(c);

                    indices.push_back(uiv1);
                    indices.push_back(uiv2);
                    indices.push_back(uiv3);

                    break;
            }
        }

        std::vector<glm::vec3> tmp(v.size(), glm::vec3(0));

        if (fmax > 1)
            for (unsigned int i = 0; i < v.size(); i++)
                v[i] = v[i] / fmax;

        if (comuputeNormals) {

            for (uint32_t i = 0; i < t.size(); i+=3) {

                glm::vec3 v1 = v[t[i][0]];
                glm::vec3 v2 = v[t[i+1][0]];
                glm::vec3 v3 = v[t[i+2][0]];

                glm::vec3 crossV = glm::normalize(glm::cross(v2-v1, v3-v1));
                tmp[t[i][0]] += crossV;
                tmp[t[i+1][0]] += crossV;
                tmp[t[i+2][0]] += crossV;
            }
        } else {
            for (unsigned int i = 0; i < t.size(); i++)
                tmp[t[i][0]] = n[t[i][1]];
        }

        for (unsigned int i = 0; i < v.size(); i++) {
            vertices.push_back(v[i][0]);
            vertices.push_back(v[i][1]);
            vertices.push_back(v[i][2]);

            normals.push_back(tmp[i][0]);
            normals.push_back(tmp[i][1]);
            normals.push_back(tmp[i][2]);
        }


        Imported3DModel myobj (vertices, normals, indices, glm::vec3(0.5,0.5,0.5));
        myobj.updateShiftedVertices();
        objects->push_back(myobj);

        obj.close();

        std::cout << fileName << " has been loaded." << std::endl;

    } else {
        std::cerr << "ERROR::LOADING SHADER::CANNOT OPEN FILE" << std::endl;
    }
}
