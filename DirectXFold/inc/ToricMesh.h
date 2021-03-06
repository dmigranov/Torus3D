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

    // ”наследовано через Mesh
    virtual void Render(std::list<DirectX::XMMATRIX> matrices) override;

    virtual void Render(DirectX::XMMATRIX matrix) override;

};

