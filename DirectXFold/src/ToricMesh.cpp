#include "pch.h"
#include "ToricMesh.h"

ToricMesh::ToricMesh() : Mesh()
{}

ToricMesh::ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices) : Mesh(nv, vertices, ni, indices)
{ }

ToricMesh::ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices, DirectX::XMMATRIX world) : Mesh(nv, vertices, ni, indices, world)
{ }
