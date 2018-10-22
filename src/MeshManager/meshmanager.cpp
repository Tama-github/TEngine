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
    _oMesh.request_vertex_normals();
    _oMesh.request_face_normals();
}


void MeshManager::convertToMaterial3DObject (Material3DObject &inMesh) {
    inMesh.getVertices().clear();
    inMesh.getIndices().clear();
    inMesh.getNormals().clear();
    OMesh::Point p;
    OMesh::Point nn;
    unsigned int i = 0;
    std::vector<GLfloat> v = std::vector<GLfloat>(_oMesh.n_vertices()*3); //Vertices
    std::vector<GLfloat> n = std::vector<GLfloat>(_oMesh.n_vertices()*3); //Normals
    std::vector<GLuint> f = std::vector<GLuint>(_oMesh.n_faces()*3); //Indices
    _oMesh.update_normals();

    for (OMesh::FaceIter f_it = _oMesh.faces_begin(); f_it != _oMesh.faces_end(); ++f_it) {
        OMesh::FaceVertexIter fv_it;
        for (fv_it = _oMesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it) {
            /*Indices*/
            f[i] = fv_it->idx();
            /*Vertices*/
            p = _oMesh.point(*fv_it);
            v[(fv_it->idx()*3)] = p[0];
            v[(fv_it->idx()*3)+1] = p[1];
            v[(fv_it->idx()*3)+2] = p[2];
            /*Normals*/
            nn = _oMesh.normal(*fv_it);
            n[(fv_it->idx()*3)] = nn[0];
            n[(fv_it->idx()*3)+1] = nn[1];
            n[(fv_it->idx()*3)+2] = nn[2];
            i++;
        }
    }
    inMesh.getVertices() = v;
    inMesh.getIndices() = f;
    inMesh.getNormals() = n;

}

void MeshManager::subdivide () {
    for (/*edge it*/;;) {
        if () { /*Application du filtre config 1*/

        } else if () { /*config 2*/

        } else if () { /*config 3*/

        } else if () { /*config 4*/

        } else { /*config parfaite*/

        }
    }
    for (/*sommet it*/;;) {

    }
}










