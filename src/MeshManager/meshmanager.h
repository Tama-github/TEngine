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

};

#endif // MESHMANAGER_H
