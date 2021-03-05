#include "pch.h"
#include "ToricMesh.h"

int ToricMesh::ReplicationCount = 10;
double ToricMesh::TorX = 5.;
double ToricMesh::TorY = 5.;
double ToricMesh::TorZ = 5.;

ToricMesh::ToricMesh() : Mesh()
{}

ToricMesh::ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices) : Mesh(nv, vertices, ni, indices)
{ }

ToricMesh::ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices, DirectX::XMMATRIX world) : Mesh(nv, vertices, ni, indices, world)
{ }
