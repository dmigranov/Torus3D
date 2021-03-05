#pragma once
#include "Mesh.h"

class ToricMesh : public Mesh
{
public:
    static int ReplicationCount;
    static double TorX, TorY, TorZ; //��� ��� ����� � ������ ��������� � ����� ����������

    ToricMesh();
    ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices);
    ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices, DirectX::XMMATRIX world);
    virtual void Render() override;

private:

};