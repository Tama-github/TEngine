#include "spheres.h"

Sphere::Sphere(glm::vec3 position, glm::vec3 color) :
    Material3DObject(position, color)
{

}

void Sphere::initUVSphere (uint32_t meridians, uint32_t parallels) {
    Mesh mesh;
    UVSphere(meridians, parallels, mesh);
    setUp(mesh);
    updateShiftedVertices();
}

void Sphere::initICOSphere (uint32_t divisions) {
    Mesh mesh;
    ICOSphere(divisions, mesh);
    setUp(mesh);
    updateShiftedVertices();
}

void Sphere::initNormalizedCube (uint32_t divisions) {
    Mesh mesh;
    NormalizedCube(divisions, mesh);
    setUp(mesh);
    updateShiftedVertices();
}

void Sphere::initSpherifiedCube (uint32_t divisions){
    Mesh mesh;
    SpherifiedCube(divisions, mesh);
    setUp(mesh);
    updateShiftedVertices();
}

void Sphere::setUp(Mesh mesh) {
    for (unsigned int i = 0; i < mesh.vertices.size(); i++) {
        _vertices.push_back(mesh.vertices[i][0]);
        _vertices.push_back(mesh.vertices[i][1]);
        _vertices.push_back(mesh.vertices[i][2]);

        _normals.push_back(mesh.normals[i][0]);
        _normals.push_back(mesh.normals[i][1]);
        _normals.push_back(mesh.normals[i][2]);
    }
    for (unsigned int i = 0; i < mesh.triangles.size(); i++) {
        _indices.push_back(mesh.triangles[i]);
    }
}

void Sphere::UVSphere(uint32_t meridians, uint32_t parallels, Mesh &mesh)
{
	mesh.vertices.emplace_back(0.0f, 1.0f, 0.0f);
	for (uint32_t j = 0; j < parallels - 1; ++j)
	{
		double const polar = M_PI * double(j+1) / double(parallels);
		double const sp = std::sin(polar);
		double const cp = std::cos(polar);
		for (uint32_t i = 0; i < meridians; ++i)
		{
			double const azimuth = 2.0 * M_PI * double(i) / double(meridians);
			double const sa = std::sin(azimuth);
			double const ca = std::cos(azimuth);
			double const x = sp * ca;
			double const y = cp;
			double const z = sp * sa;
			mesh.vertices.emplace_back(x, y, z);
		}
	}
	mesh.vertices.emplace_back(0.0f, -1.0f, 0.0f);

	for (uint32_t i = 0; i < meridians; ++i)
	{
		uint32_t const a = i + 1;
		uint32_t const b = (i + 1) % meridians + 1;
		mesh.addTriangle(0, b, a);
	}

	for (uint32_t j = 0; j < parallels - 2; ++j)
	{
		uint32_t aStart = j * meridians + 1;
		uint32_t bStart = (j + 1) * meridians + 1;
		for (uint32_t i = 0; i < meridians; ++i)
		{
			const uint32_t a = aStart + i;
			const uint32_t a1 = aStart + (i + 1) % meridians;
			const uint32_t b = bStart + i;
			const uint32_t b1 = bStart + (i + 1) % meridians;
			mesh.addQuad(a, a1, b1, b);
		}
	}

	for (uint32_t i = 0; i < meridians; ++i)
	{
		uint32_t const a = i + meridians * (parallels - 2) + 1;
		uint32_t const b = (i + 1) % meridians + meridians * (parallels - 2) + 1;
		mesh.addTriangle(mesh.vertices.size() - 1, a, b);
	}
	calculNormals(mesh);
}

void Sphere::calculNormals(Mesh &mesh) {
	mesh.normals = std::vector<glm::vec3>(mesh.vertices.size(), glm::vec3(0));
	
	for (uint32_t i = 0; i < mesh.triangles.size(); i+=3) {
        glm::vec3 v1 = mesh.vertices[mesh.triangles[i]];
        glm::vec3 v2 = mesh.vertices[mesh.triangles[i+1]];
        glm::vec3 v3 = mesh.vertices[mesh.triangles[i+2]];
        
	    glm::vec3 tmp = glm::cross(v2-v1, v2-v3);
	    mesh.normals[mesh.triangles[i]] += tmp;
	    mesh.normals[mesh.triangles[i+1]] += tmp;
	    mesh.normals[mesh.triangles[i+2]] += tmp;
	}

	for (uint32_t i = 0; i < mesh.normals.size(); i++) 
	     mesh.normals[i] = glm::normalize(mesh.normals[i]);
}

void Sphere::NormalizedCube(uint32_t divisions, Mesh &mesh)
{
	const double step = 1.0 / double(divisions);
	const glm::vec3 step3(step, step, step);

	for (uint32_t face = 0; face < 6; ++face)
	{
		const glm::vec3 origin = CubeToSphere::origins[face];
		const glm::vec3 right = CubeToSphere::rights[face];
		const glm::vec3 up = CubeToSphere::ups[face];
		for (uint32_t j = 0; j < divisions + 1; ++j)
		{
			const glm::vec3 j3(j, j, j);
			for (uint32_t i = 0; i < divisions + 1; ++i)
			{
				const glm::vec3 i3(i, i, i);
				const glm::vec3 p = origin + step3 * (i3 * right + j3 * up);
				mesh.vertices.emplace_back(normalize(p));
			}
		}
	}

	const uint32_t k = divisions + 1;
	for (uint32_t face = 0; face < 6; ++face)
	{
		for (uint32_t j = 0; j < divisions; ++j)
		{
			const bool bottom = j < (divisions / 2);
			for (uint32_t i = 0; i < divisions; ++i)
			{
				const bool left = i < (divisions / 2);
				const uint32_t a = (face * k + j) * k + i;
				const uint32_t b = (face * k + j) * k + i + 1;
				const uint32_t c = (face * k + j + 1) * k + i;
				const uint32_t d = (face * k + j + 1) * k + i + 1;
				if (bottom ^ left) mesh.addQuadAlt(a, c, d, b);
				else mesh.addQuad(a, c, d, b);
			}
		}
	}
	calculNormals(mesh);
}

void Sphere::SpherifiedCube(uint32_t divisions, Mesh &mesh)
{
	const double step = 1.0 / double(divisions);
	const glm::vec3 step3(step, step, step);

	for (uint32_t face = 0; face < 6; ++face)
	{
		const glm::vec3 origin = CubeToSphere::origins[face];
		const glm::vec3 right = CubeToSphere::rights[face];
		const glm::vec3 up = CubeToSphere::ups[face];
		for (uint32_t j = 0; j < divisions + 1; ++j)
		{
			const glm::vec3 j3(j, j, j);
			for (uint32_t i = 0; i < divisions + 1; ++i)
			{
				const glm::vec3 i3(i, i, i);
				const glm::vec3 p = origin + step3 * (i3 * right + j3 * up);
				const glm::vec3 p2 = p * p;
				const glm::vec3 n
				(
					p.x * std::sqrt(1.0 - 0.5 * (p2.y + p2.z) + p2.y*p2.z / 3.0),
					p.y * std::sqrt(1.0 - 0.5 * (p2.z + p2.x) + p2.z*p2.x / 3.0),
					p.z * std::sqrt(1.0 - 0.5 * (p2.x + p2.y) + p2.x*p2.y / 3.0)
				);
				mesh.vertices.emplace_back(n);
			}
		}
	}

	const uint32_t k = divisions + 1;
	for (uint32_t face = 0; face < 6; ++face)
	{
		for (uint32_t j = 0; j < divisions; ++j)
		{
			const bool bottom = j < (divisions / 2);
			for (uint32_t i = 0; i < divisions; ++i)
			{
				const bool left = i < (divisions / 2);
				const uint32_t a = (face * k + j) * k + i;
				const uint32_t b = (face * k + j) * k + i + 1;
				const uint32_t c = (face * k + j + 1) * k + i;
				const uint32_t d = (face * k + j + 1) * k + i + 1;
				if (bottom ^ left) mesh.addQuadAlt(a, c, d, b);
				else mesh.addQuad(a, c, d, b);
			}
		}
	}
	calculNormals(mesh);
}

void Sphere::Icosahedron(Mesh &mesh)
{
	const double t = (1.0 + std::sqrt(5.0)) / 2.0;

	// Vertices
	mesh.vertices.emplace_back(normalize(glm::vec3(-1.0,  t, 0.0)));
	mesh.vertices.emplace_back(normalize(glm::vec3( 1.0,  t, 0.0)));
	mesh.vertices.emplace_back(normalize(glm::vec3(-1.0, -t, 0.0)));
	mesh.vertices.emplace_back(normalize(glm::vec3( 1.0, -t, 0.0)));
	mesh.vertices.emplace_back(normalize(glm::vec3(0.0, -1.0,  t)));
	mesh.vertices.emplace_back(normalize(glm::vec3(0.0,  1.0,  t)));
	mesh.vertices.emplace_back(normalize(glm::vec3(0.0, -1.0, -t)));
	mesh.vertices.emplace_back(normalize(glm::vec3(0.0,  1.0, -t)));
	mesh.vertices.emplace_back(normalize(glm::vec3( t, 0.0, -1.0)));
	mesh.vertices.emplace_back(normalize(glm::vec3( t, 0.0,  1.0)));
	mesh.vertices.emplace_back(normalize(glm::vec3(-t, 0.0, -1.0)));
	mesh.vertices.emplace_back(normalize(glm::vec3(-t, 0.0,  1.0)));

	// Faces
	mesh.addTriangle(0, 11, 5);
	mesh.addTriangle(0, 5, 1);
	mesh.addTriangle(0, 1, 7);
	mesh.addTriangle(0, 7, 10);
	mesh.addTriangle(0, 10, 11);
	mesh.addTriangle(1, 5, 9);
	mesh.addTriangle(5, 11, 4);
	mesh.addTriangle(11, 10, 2);
	mesh.addTriangle(10, 7, 6);
	mesh.addTriangle(7, 1, 8);
	mesh.addTriangle(3, 9, 4);
	mesh.addTriangle(3, 4, 2);
	mesh.addTriangle(3, 2, 6);
	mesh.addTriangle(3, 6, 8);
	mesh.addTriangle(3, 8, 9);
	mesh.addTriangle(4, 9, 5);
	mesh.addTriangle(2, 4, 11);
	mesh.addTriangle(6, 2, 10);
	mesh.addTriangle(8, 6, 7);
	mesh.addTriangle(9, 8, 1);
}



uint32_t Sphere::subdivideEdge(uint32_t f0, uint32_t f1, const glm::vec3 &v0, const glm::vec3 &v1, Mesh &io_mesh, std::map<Edge, uint32_t> &io_divisions)
{
	const Edge edge(f0, f1);
	auto it = io_divisions.find(edge);
	
	if (it != io_divisions.end())
	{
		return it->second;
	}

	const glm::vec3 v = normalize(glm::vec3(0.5) * (v0 + v1));
	const uint32_t f = io_mesh.vertices.size();
	io_mesh.vertices.emplace_back(v);
	io_divisions.emplace(edge, f);
	return f;
}

void Sphere::SubdivideMesh(const Mesh &meshIn, Mesh &meshOut)
{
	meshOut.vertices = meshIn.vertices;

	std::map<Edge, uint32_t> divisions; // Edge -> new vertex
	
	meshOut.triangles.clear();

	for (uint32_t i = 0; i < meshIn.triangleCount(); ++i)
	{
		const uint32_t f0 = meshIn.triangles[i * 3];
		const uint32_t f1 = meshIn.triangles[i * 3 + 1];
		const uint32_t f2 = meshIn.triangles[i * 3 + 2];

		const glm::vec3 v0 = meshIn.vertices[f0];
		const glm::vec3 v1 = meshIn.vertices[f1];
		const glm::vec3 v2 = meshIn.vertices[f2];

		const uint32_t f3 = subdivideEdge(f0, f1, v0, v1, meshOut, divisions);
		const uint32_t f4 = subdivideEdge(f1, f2, v1, v2, meshOut, divisions);
		const uint32_t f5 = subdivideEdge(f2, f0, v2, v0, meshOut, divisions);

		meshOut.addTriangle(f0, f3, f5);
		meshOut.addTriangle(f3, f1, f4);
		meshOut.addTriangle(f4, f2, f5);
		meshOut.addTriangle(f3, f4, f5);
	}
}

void Sphere::ICOSphere(uint32_t divisions, Mesh &mesh)
{
    Mesh mD;
    Icosahedron(mesh);
    for (unsigned int i = 0; i < divisions; i++) {
        SubdivideMesh(mesh, mD);
        mesh.vertices = mD.vertices;
        mesh.triangles = mD.triangles;
    }
    
    calculNormals(mesh);
}

