#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include "../Materials/material3DObject.h"
#include <OpenMesh/Core/Geometry/QuadricT.hh>
#include <set>

typedef OpenMesh::TriMesh_ArrayKernelT<> OMesh;

class MeshManager {
public:
    MeshManager() :
        _oMesh (OMesh())
    {};

    void useMaterial3DObject (Material3DObject inMesh);
    void convertToMaterial3DObject (Material3DObject &inMesh);
    void subdivide ();
    void simplificationHEC (unsigned int nbMaxFaces);

private:
    OMesh _oMesh;
    const std::vector<float> _subdivCoef = {1.f/16.f, 2.f/16.f, 4.f/16.f};

    bool isPerfectConfig(OMesh::EdgeHandle eh);
    OMesh::Point edgeNewPoint(OMesh::EdgeHandle eh);
    OMesh::Point vertexNewPoint(OMesh::VertexHandle eh);
    OpenMesh::VPropHandleT<OpenMesh::Geometry::Quadricf> _Q;

    void buildQuadric();
    bool isCollapsable(OMesh::EdgeHandle edge);
    float computeError (OMesh::HalfedgeHandle heh);
    std::set<OMesh::VertexHandle> getVertexToUpdate(OMesh::HalfedgeHandle heh);
    void simplificationHECInit(std::map<float,OMesh::HalfedgeHandle>& priority);

};

#endif // MESHMANAGER_H
