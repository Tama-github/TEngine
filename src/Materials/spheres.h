#ifndef SPHERES_H
#define SPHERES_H

//https://github.com/caosdoar/spheres/blob/master/src/spheres.cpp


#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>


#include <glm/glm.hpp>

#include "material3DObject.h"

namespace CubeToSphere
{
    static const glm::vec3 origins[6] =
    {
	    glm::vec3(-1.0, -1.0, -1.0),
	    glm::vec3(1.0, -1.0, -1.0),
	    glm::vec3(1.0, -1.0, 1.0),
	    glm::vec3(-1.0, -1.0, 1.0),
	    glm::vec3(-1.0, 1.0, -1.0),
	    glm::vec3(-1.0, -1.0, 1.0)
    };
    static const glm::vec3 rights[6] =
    {
	    glm::vec3(2.0, 0.0, 0.0),
	    glm::vec3(0.0, 0.0, 2.0),
	    glm::vec3(-2.0, 0.0, 0.0),
	    glm::vec3(0.0, 0.0, -2.0),
	    glm::vec3(2.0, 0.0, 0.0),
	    glm::vec3(2.0, 0.0, 0.0)
    };
    static const glm::vec3 ups[6] =
    {
	    glm::vec3(0.0, 2.0, 0.0),
	    glm::vec3(0.0, 2.0, 0.0),
	    glm::vec3(0.0, 2.0, 0.0),
	    glm::vec3(0.0, 2.0, 0.0),
	    glm::vec3(0.0, 0.0, 2.0),
	    glm::vec3(0.0, 0.0, -2.0)
    };
}

class Sphere : public Material3DObject {
public:    
    struct Mesh
    {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<uint32_t> triangles;

        uint32_t triangleCount() const { return triangles.size() / 3; }

        void addTriangle(uint32_t a, uint32_t b, uint32_t c)
        {
            triangles.emplace_back(a);
            triangles.emplace_back(b);
            triangles.emplace_back(c);
        }

        void addQuad(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
        {
            triangles.emplace_back(a);
            triangles.emplace_back(b);
            triangles.emplace_back(c);
            triangles.emplace_back(a);
            triangles.emplace_back(c);
            triangles.emplace_back(d);
        }
        
        void addQuadAlt(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
	    {
		    triangles.emplace_back(a);
		    triangles.emplace_back(b);
		    triangles.emplace_back(d);
		    triangles.emplace_back(b);
		    triangles.emplace_back(c);
		    triangles.emplace_back(d);
        }

        void clear()
        {
            vertices.clear();
            triangles.clear();
        }
        
        void UVSphere(uint32_t meridians, uint32_t parallels, Mesh &mesh);

    };
    
    struct Edge
    {
	    uint32_t v0;
	    uint32_t v1;

	    Edge(uint32_t v0, uint32_t v1)
		    : v0(v0 < v1 ? v0 : v1)
		    , v1(v0 < v1 ? v1 : v0)
	    {
	    }

	    bool operator <(const Edge &rhs) const
	    {
		    return v0 < rhs.v0 || (v0 == rhs.v0 && v1 < rhs.v1);
	    }
    };
    

    Sphere(glm::vec3 position, glm::vec3 color);
    void initUVSphere (uint32_t meridians, uint32_t parallels);
    void initICOSphere(uint32_t divisions);
    void initNormalizedCube(uint32_t divisions);
    void initSpherifiedCube(uint32_t divisions);

private:
    glm::vec3 _color;
    void UVSphere(uint32_t meridians, uint32_t parallels, Mesh &mesh);
    void calculNormals(Mesh &mesh);
    void NormalizedCube(uint32_t divisions, Mesh &mesh);
    void SpherifiedCube(uint32_t divisions, Mesh &mesh);
    void Icosahedron(Mesh &mesh);
    uint32_t subdivideEdge(uint32_t f0, uint32_t f1, const glm::vec3 &v0, const glm::vec3 &v1, Mesh &io_mesh, std::map<Edge, uint32_t> &io_divisions);
    void SubdivideMesh(const Mesh &meshIn, Mesh &meshOut);
    void ICOSphere(uint32_t divisions, Mesh &mesh);
    void setUp(Mesh mesh);


};



#endif // SPHERES_H
