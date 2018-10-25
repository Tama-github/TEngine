#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include "../Materials/material3DObject.h"

typedef OpenMesh::TriMesh_ArrayKernelT<> OMesh;

class MeshManager {
public:
    MeshManager() :
        _oMesh (OMesh())
    {};

    void useMaterial3DObject (Material3DObject inMesh);
    void convertToMaterial3DObject (Material3DObject &inMesh);
    void subdivide ();

private:
    OMesh _oMesh;
    const std::vector<float> _subdivCoef = {1.f/16.f, 2.f/16.f, 4.f/16.f};

    bool isPerfectConfig(OMesh::EdgeHandle eh);
    OMesh::Point edgeNewPoint(OMesh::EdgeHandle eh);
    OMesh::Point vertexNewPoint(OMesh::VertexHandle eh);

};

#endif // MESHMANAGER_H
