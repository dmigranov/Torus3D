#pragma once
#include "Mesh.h"
class Camera;

class CameraMesh :
    public Mesh
{
public:
    CameraMesh(Camera* camera);

    // Inherited via Mesh
    virtual void Render(std::list<DirectX::XMMATRIX> matrices) override;
    virtual void Render() override;
    virtual void Render(DirectX::XMMATRIX matrix) override;
};

