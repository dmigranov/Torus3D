#pragma once
#include "Mesh.h"

class ToricMesh : public Mesh
{
public:
    ToricMesh();
    ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices);
    ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices, DirectX::XMMATRIX world);
private:

};