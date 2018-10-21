#include "meshmanager.h"

void MeshManager::useMaterial3DObject (Material3DObject inMesh) {
    auto vertices = inMesh.getVertices();
    unsigned int n = vertices.size();
    std::vector<OMesh::VertexHandle> vhandle;

    for (unsigned int i = 0; i < n; i+=3) {
        vhandle.push_back(_oMesh.add_vertex(OMesh::Point(vertices[i],vertices[i+1],vertices[i+2])));
    }

    std::vector<OMesh::VertexHandle> face_vhandles;
    auto triangles = inMesh.getIndices();
    unsigned int m = triangles.size();
    for (unsigned int i = 0; i < m; i+=3) {
        face_vhandles.clear();
        face_vhandles.push_back(vhandle[triangles[i]]);
        face_vhandles.push_back(vhandle[triangles[i+1]]);
        face_vhandles.push_back(vhandle[triangles[i+2]]);
        _oMesh.add_face(face_vhandles);
    }
}


void MeshManager::convertToMaterial3DObject (Material3DObject &inMesh) {
    inMesh.getVertices().clear();
    inMesh.getIndices().clear();
    OMesh::Point p;
    unsigned int i = 0;
    for (OMesh::VertexIter v_it = _oMesh.vertices_begin(); v_it != _oMesh.vertices_end(); ++v_it) {
        p = _oMesh.point(*v_it);
        inMesh.getVertices().push_back(p[0]);
        inMesh.getVertices().push_back(p[1]);
        inMesh.getVertices().push_back(p[2]);
    }
    i=0;
    for (OMesh::FaceIter f_it = _oMesh.faces_begin(); f_it != _oMesh.faces_end(); ++f_it) {
        OMesh::FaceVertexIter fv_it;
        for (fv_it = _oMesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it) {
            std::cout << "idx = " << fv_it->idx() << std::endl;
            inMesh.getIndices()[i++] = fv_it->idx();
        }
    }

}
