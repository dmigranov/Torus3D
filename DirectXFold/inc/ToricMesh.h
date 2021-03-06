#pragma once
#include "Mesh.h"

class ToricMesh : public Mesh
{
public:
    struct InstanceType
    {
        DirectX::SimpleMath::Vector3 position;
    };

    static int ReplicationCount;
    static double TorX, TorY, TorZ; //все это будет в классе рендерера в общей реализации

    ToricMesh();
    ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices);
    ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices, DirectX::XMMATRIX world);
    
    virtual void Render() override;

private:

};

int ToricMesh::ReplicationCount = 10;
double ToricMesh::TorX = 5.;
double ToricMesh::TorY = 5.;
double ToricMesh::TorZ = 5.;