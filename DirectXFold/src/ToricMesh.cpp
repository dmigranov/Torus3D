#include "pch.h"
#include "ToricMesh.h"

#include "Game.h"

int ToricMesh::ReplicationCount = 10;
double ToricMesh::TorX = 5.;
double ToricMesh::TorY = 5.;
double ToricMesh::TorZ = 5.;

using namespace DirectX::SimpleMath;

ToricMesh::ToricMesh() : Mesh()
{
    D3D11_BUFFER_DESC instanceBufferDesc;
    D3D11_SUBRESOURCE_DATA instanceData;
    HRESULT result;

    auto& game = Game::GetInstance();
    auto device = game.g_d3dDevice;
    deviceContext = game.g_d3dDeviceContext;
    d3dConstantBuffer = game.g_d3dVSConstantBuffers[2];


    int instanceCountPerDimension = (2 * ReplicationCount + 1);
    int instanceCount = instanceCountPerDimension * instanceCountPerDimension * instanceCountPerDimension;
    auto instances = new InstanceType[instanceCount];
    if (!instances)
    {
        throw std::exception("Can't create instances array");
    }

    for (int Xi = -ReplicationCount; Xi <= ReplicationCount; Xi++)
    {
        double x = Xi * TorX;
        for (int Yi = -ReplicationCount; Yi <= ReplicationCount; Yi++)
        {
            double y = Yi * TorY;
            for (int Zi = -ReplicationCount; Zi < ReplicationCount; Zi++)
            {
                double z = Zi * TorZ;

                instances[(Zi + ReplicationCount) * instanceCountPerDimension * instanceCountPerDimension +
                    (Yi + ReplicationCount) * instanceCountPerDimension +
                    (Xi + ReplicationCount)].position = Vector3(x, y, z);
            }
        }
    }


    instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    instanceBufferDesc.ByteWidth = sizeof(InstanceType) * instanceCount;
    instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    instanceBufferDesc.CPUAccessFlags = 0;
    instanceBufferDesc.MiscFlags = 0;
    instanceBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the instance data.
    instanceData.pSysMem = instances;
    instanceData.SysMemPitch = 0;
    instanceData.SysMemSlicePitch = 0;




    // Create the instance buffer.
    result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &g_d3dInstanceBuffer);
    if (FAILED(result))
    {
        //todo: ошибка...
        return;
    }

    // Release the instance array now that the instance buffer has been created and loaded.
    delete[] instances;
    instances = 0;


}

ToricMesh::ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices) : Mesh(nv, vertices, ni, indices)
{
    //todo
}

ToricMesh::ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices, DirectX::XMMATRIX world) : Mesh(nv, vertices, ni, indices, world)
{ 
    //todo
}

void ToricMesh::Render()
{
    const UINT vertexStride = sizeof(VertexPosColor);   //Each stride is the size (in bytes) of the elements that are to be used from that vertex buffer.
    const UINT offset = 0;
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->IASetVertexBuffers(0, 1, &g_d3dVertexBuffer, &vertexStride, &offset);
    deviceContext->IASetIndexBuffer(g_d3dIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    if (m_texture != nullptr)
    {     //Pixel Shader Stafe - unique 4 every stage
        auto shaderResource = m_texture->GetTexture();
        deviceContext->PSSetShaderResources(0, 1, &shaderResource);
    }


    MeshConstantBuffer constantBufferTemp = { constantBuffer.m_world };
    if (parentMesh != nullptr)
        constantBufferTemp.m_world = constantBufferTemp.m_world * parentMesh->GetWorldMatrix(); //это правильный порядок
    deviceContext->UpdateSubresource(d3dConstantBuffer, 0, nullptr, &constantBufferTemp, 0, 0);

    //DRAW
    deviceContext->DrawIndexedInstanced(indicesCount, 1, 0, 0, 0);

}

void ToricMesh::Render(std::list<DirectX::XMMATRIX> matrices)
{
    //todo
}

void ToricMesh::Render(DirectX::XMMATRIX matrix)
{
    //todo
}