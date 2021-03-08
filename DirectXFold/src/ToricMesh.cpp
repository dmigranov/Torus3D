#include "pch.h"
#include "ToricMesh.h"

#include "Game.h"

int ToricMesh::ReplicationCount = 14;
double ToricMesh::TorX = 40.;
double ToricMesh::TorY = 40.;
double ToricMesh::TorZ = 40.;

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


    m_instanceCountPerDimension = (2 * ReplicationCount + 1);
    m_instanceCount = m_instanceCountPerDimension * m_instanceCountPerDimension * m_instanceCountPerDimension;
    
    auto instances = new InstanceType[m_instanceCount];
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
            for (int Zi = -ReplicationCount; Zi <= ReplicationCount; Zi++)
            {
                double z = Zi * TorZ;

                instances[(Zi + ReplicationCount) * m_instanceCountPerDimension * m_instanceCountPerDimension +
                    (Yi + ReplicationCount) * m_instanceCountPerDimension +
                    (Xi + ReplicationCount)].position = Vector3(x, y, z);
            }
        }
    }


    instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    //instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_instanceCount;
    instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    instanceBufferDesc.CPUAccessFlags = 0;
    //instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
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
    //чтобы пространство было бесконечным,
    //но это не поможет, если двигаться будут объекты
    //потому надо ещё учитывать мировую матрицу объекта - 
    //то есть матрица "центрового" объекта
    auto camera = Game::GetInstance().m_camera;
    Vector4 cameraPos = camera->GetPosition();
    double x = cameraPos.x, z = cameraPos.z, y = cameraPos.y;
    double xm = std::fmodl(x, TorX), zm = std::fmodl(z, TorZ), ym = std::fmodl(y, TorY);

    auto meshWorld = constantBuffer.m_world;
    Vector4 worldPos = Vector4::Transform(Vector4(0, 0, 0, 1), meshWorld);
    double wx = worldPos.x, wz = worldPos.z, wy = worldPos.y;

    int wxm, wym, wzm; 
    std::remquol(wx, TorX, &wxm);
    std::remquol(wz, TorZ, &wzm);
    std::remquol(wy, TorY, &wym);

    camera->SetPosition(xm + wxm * TorX, ym + wym * TorY, zm + wzm * TorZ);


    //The instance buffer is just a second vertex buffer containing different   
    //information so it is set on the device at the same time /using the same call
    //as the vertex buffer. So instead of how we previously sent in a single stride, 
    //offset, and buffer we now send an array of strides, offsets, and buffers 
    //to the IASetVertexBuffers call. 

    //const UINT vertexStride = sizeof(VertexPosColor);   //Each stride is the size (in bytes) of the elements that are to be used from that vertex buffer.
    const unsigned int vertexStrides[2] = { sizeof(VertexPosColor), sizeof(InstanceType)};
    //unsigned int offsets[2];
    const unsigned int offsets[2] = { 0, 0 };
    ID3D11Buffer* bufferPointers[2] = { g_d3dVertexBuffer, g_d3dInstanceBuffer };





    const UINT offset = 0;
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //deviceContext->IASetVertexBuffers(0, 1, &g_d3dVertexBuffer, &vertexStride, &offset);
    deviceContext->IASetVertexBuffers(0, 2, bufferPointers, vertexStrides, offsets);
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
    deviceContext->DrawIndexedInstanced(indicesCount, m_instanceCount, 0, 0, 0);

}

void ToricMesh::Render(std::list<DirectX::XMMATRIX> matrices)
{
    //todo
}

void ToricMesh::Render(DirectX::XMMATRIX matrix)
{
    //todo
}