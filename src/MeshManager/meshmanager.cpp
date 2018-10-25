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
    _oMesh.request_face_status();
    _oMesh.request_edge_status();
    _oMesh.request_vertex_status();
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


bool MeshManager::isPerfectConfig(OMesh::EdgeHandle eh) {
    // Principal edge is boundary
    if (_oMesh.is_boundary(eh))
        return false;

    OMesh::HalfedgeHandle heh0 = _oMesh.halfedge_handle(eh, 0);

    heh0 = _oMesh.next_halfedge_handle(heh0);
    //No first wing
    if (_oMesh.is_boundary(_oMesh.edge_handle(heh0)))
        return false;

    heh0 = _oMesh.next_halfedge_handle(heh0);
    //No second wing
    if (_oMesh.is_boundary(_oMesh.edge_handle(heh0)))
        return false;

    heh0 = _oMesh.halfedge_handle(eh, 1);

    heh0 = _oMesh.next_halfedge_handle(heh0);
    //No third wing
    if (_oMesh.is_boundary(_oMesh.edge_handle(heh0)))
        return false;

    heh0 = _oMesh.next_halfedge_handle(heh0);
    //No fourth wing
    if (_oMesh.is_boundary(_oMesh.edge_handle(heh0)))
        return false;

    return true;
}

OMesh::Point MeshManager::edgeNewPoint(OMesh::EdgeHandle eh) {
    OMesh::Point res = {0,0,0};
    //Next
    OMesh::HalfedgeHandle heh0;
    OMesh::HalfedgeHandle heh1;
    //Oposite
    OMesh::HalfedgeHandle hehOpo0;
    OMesh::HalfedgeHandle hehOpo1;

    //Vertex primaire
    heh0 = _oMesh.halfedge_handle(eh, 0);
    res += _oMesh.point(_oMesh.to_vertex_handle(heh0))*_subdivCoef[2];
    heh1 = _oMesh.halfedge_handle(eh, 1);
    res += _oMesh.point(_oMesh.to_vertex_handle(heh1))*_subdivCoef[2];

    //Vertex secondaire
    heh0 = _oMesh.next_halfedge_handle(heh0);
    res += _oMesh.point(_oMesh.to_vertex_handle(heh0))*_subdivCoef[1];
    heh1 = _oMesh.next_halfedge_handle(heh1);
    res += _oMesh.point(_oMesh.to_vertex_handle(heh1))*_subdivCoef[1];

    //Vertex tertiaire Première aile
    hehOpo0 = _oMesh.next_halfedge_handle(_oMesh.opposite_halfedge_handle(heh0));
    res += _oMesh.point(_oMesh.to_vertex_handle(hehOpo0))*_subdivCoef[0];
    hehOpo1 = _oMesh.next_halfedge_handle(_oMesh.opposite_halfedge_handle(heh1));
    res += _oMesh.point(_oMesh.to_vertex_handle(hehOpo1))*_subdivCoef[0];

    //Vertex tertiaire Deuxième aile
    heh0 = _oMesh.next_halfedge_handle(heh0);
    hehOpo0 = _oMesh.next_halfedge_handle(_oMesh.opposite_halfedge_handle(heh0));
    res += _oMesh.point(_oMesh.to_vertex_handle(hehOpo0))*_subdivCoef[0];
    heh1 = _oMesh.next_halfedge_handle(heh1);
    hehOpo1 = _oMesh.next_halfedge_handle(_oMesh.opposite_halfedge_handle(heh1));
    res += _oMesh.point(_oMesh.to_vertex_handle(hehOpo1))*_subdivCoef[0];

    std::cout << "new point = " << "( " << res[0] << " " << res[1] << " " << res[2] << " " << ")" << std::endl;

    return res;
}

OMesh::Point MeshManager::vertexNewPoint(OMesh::VertexHandle vh) {
    OMesh::Point res = {0,0,0};
    int valance = 0;
    float alpha = 0.f;
    for (OMesh::VertexVertexIter vv_it = _oMesh.vv_iter(vh); vv_it.is_valid(); ++vv_it) {
        valance++;
    }
    if (valance == 3) {
        alpha = 3.f/16.f;
    } else if (valance > 3) {
        alpha = 3.f/(8.f*valance);
    }
    std::cout << "valance = " << valance << " / alpha = " << alpha << std::endl;
    for (OMesh::VertexVertexIter vv_it = _oMesh.vv_iter(vh); vv_it.is_valid(); ++vv_it) {
        res += alpha*_oMesh.point(*vv_it);
    }
    res += _oMesh.point(vh)*(1-valance*alpha);
    std::cout << "new point = " << "( " << res[0] << " " << res[1] << " " << res[2] << " " << ")" << std::endl;
    return res;
}

void MeshManager::subdivide () {
    //ADD PROPERTIES
    std::cout << "ADD PROPERTIES" << std::endl;
    OpenMesh::EPropHandleT<OMesh::Point> newVertexPosOnEdge;
    OpenMesh::EPropHandleT<OMesh::VertexHandle> newHandleVertexPosOnEdge;
    _oMesh.add_property(newVertexPosOnEdge);
    _oMesh.add_property(newHandleVertexPosOnEdge);

    OpenMesh::VPropHandleT<OMesh::Point> newVertexPosOnVertex;
    OpenMesh::VPropHandleT<OMesh::VertexHandle> newHandleVertexPosOnVertex;

    std::cout << "ici hein ?" << std::endl;
    OpenMesh::VPropHandleT<bool> isOld;
    std::cout << "oui" << std::endl;
    _oMesh.add_property(newVertexPosOnVertex);
    _oMesh.add_property(newHandleVertexPosOnVertex);
    _oMesh.add_property(isOld);

    //Update all vertices
    std::cout << "Update all vertices" << std::endl;
    for (OMesh::VertexIter v_it = _oMesh.vertices_begin(); v_it != _oMesh.vertices_end(); ++v_it) {
        _oMesh.property(isOld,*v_it) = true;
    }

    OMesh::Point p;
    OMesh::VertexHandle vh;
    //Edges Treatment
    std::cout << "Traitement des Edges" << std::endl;
    for (OMesh::EdgeIter e_it = _oMesh.edges_begin(); e_it != _oMesh.edges_end(); ++e_it) {
        if (isPerfectConfig(*e_it)) {
            std::cout << "perfect" << std::endl;
            p = edgeNewPoint(*e_it);
            _oMesh.property(newVertexPosOnEdge,*e_it) = p;
            vh = _oMesh.add_vertex(p);
            _oMesh.property(newHandleVertexPosOnEdge,*e_it) = vh;
            _oMesh.property(isOld,vh) = false;
        }
    }

    //Vertices Treatment
    std::cout << "Traitement des Vertices" << std::endl;
    for (OMesh::VertexIter v_it = _oMesh.vertices_begin(); v_it != _oMesh.vertices_end(); ++v_it) {
        if (!_oMesh.is_boundary(*v_it) && _oMesh.property(isOld,*v_it)) {
            p = vertexNewPoint(*v_it);
            _oMesh.property(newVertexPosOnVertex,*v_it) = p;
            vh = _oMesh.add_vertex(p);
            _oMesh.property(newHandleVertexPosOnVertex,*v_it) = vh;
            _oMesh.property(isOld,vh) = false;
        }
    }

    std::vector<std::vector<OMesh::VertexHandle>> newFaces;

    //Create new Faces
    std::cout << "Create new Faces" << std::endl;
    for (OMesh::FaceIter f_it = _oMesh.faces_begin(); f_it != _oMesh.faces_end(); ++f_it) {
        if(!_oMesh.is_boundary(*f_it, true)){
            //Experimental
            std::vector<OMesh::VertexHandle> t0;
            std::vector<OMesh::VertexHandle> t1;
            std::vector<OMesh::VertexHandle> t2;
            std::vector<OMesh::VertexHandle> t3;
            OMesh::FaceEdgeIter fe_it = _oMesh.fe_iter(*f_it);
            OMesh::Point res = {0,0,0};
            vh = _oMesh.property(newHandleVertexPosOnEdge, *fe_it);
            res = _oMesh.point(vh);
            std::cout << "new point = " << "( " << res[0] << " " << res[1] << " " << res[2] << " " << ")" << std::endl;

            t0.push_back(vh);
            t3.push_back(vh);
            t2.push_back(vh);

            vh = _oMesh.property(newHandleVertexPosOnVertex,_oMesh.to_vertex_handle(_oMesh.halfedge_handle(*fe_it, 0)));
            res = _oMesh.point(vh);
            std::cout << "new point = " << "( " << res[0] << " " << res[1] << " " << res[2] << " " << ")" << std::endl;
            t0.push_back(vh);

            fe_it++;
            vh = _oMesh.property(newHandleVertexPosOnEdge, *fe_it);
            res = _oMesh.point(vh);
            std::cout << "new point = " << "( " << res[0] << " " << res[1] << " " << res[2] << " " << ")" << std::endl;
            t0.push_back(vh);
            t3.push_back(vh);
            t1.push_back(vh);

            vh = _oMesh.property(newHandleVertexPosOnVertex,_oMesh.to_vertex_handle(_oMesh.halfedge_handle(*fe_it, 0)));
            res = _oMesh.point(vh);
            std::cout << "new point = " << "( " << res[0] << " " << res[1] << " " << res[2] << " " << ")" << std::endl;
            t1.push_back(vh);

            fe_it++;
            vh = _oMesh.property(newHandleVertexPosOnEdge, *fe_it);
            res = _oMesh.point(vh);
            std::cout << "new point = " << "( " << res[0] << " " << res[1] << " " << res[2] << " " << ")" << std::endl;
            t2.push_back(vh);
            t3.push_back(vh);
            t1.push_back(vh);

            vh = _oMesh.property(newHandleVertexPosOnVertex,_oMesh.to_vertex_handle(_oMesh.halfedge_handle(*fe_it, 0)));
            res = _oMesh.point(vh);
            std::cout << "new point = " << "( " << res[0] << " " << res[1] << " " << res[2] << " " << ")" << std::endl;
            t2.push_back(vh);

            newFaces.push_back(t0);
            newFaces.push_back(t1);
            newFaces.push_back(t2);
            newFaces.push_back(t3);
        }
    }

    //Delete old Faces
    std::cout << "Delete old Faces" << std::endl;
    for (OMesh::FaceIter f_it = _oMesh.faces_begin(); f_it != _oMesh.faces_end(); ++f_it) {
        _oMesh.delete_face(*f_it,false);
    }

    //Delete old Vertices
    std::cout << "Delete old Vertices" << std::endl;
    for (OMesh::VertexIter v_it = _oMesh.vertices_begin(); v_it != _oMesh.vertices_end(); ++v_it) {
        if (_oMesh.property(isOld,*v_it)) {
            _oMesh.delete_vertex(*v_it);
        }
    }

    //Add new Faces
    std::cout << "Add new Faces" << std::endl;
    for (unsigned int i = 0; i < newFaces.size(); i++) {
        _oMesh.add_face(newFaces[i]);
    }

    _oMesh.garbage_collection();

    std::cout << "end : " << _oMesh.n_vertices() << std::endl;


}










