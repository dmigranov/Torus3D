#include "pch.h"
#include "ToricMesh.h"

unsigned int ToricMesh::ReplicationCount = 10;
double ToricMesh::TorX = 5.;
double ToricMesh::TorY = 5.;
double ToricMesh::TorZ = 5.;

ToricMesh::ToricMesh() : Mesh()
{}

ToricMesh::ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices) : Mesh(nv, vertices, ni, indices)
{ }

ToricMesh::ToricMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices, DirectX::XMMATRIX world) : Mesh(nv, vertices, ni, indices, world)
{ }

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

    unsigned int instanceCount = (2 * ReplicationCount + 1);
    instanceCount = instanceCount * instanceCount * instanceCount;

    MeshConstantBuffer constantBufferTemp = { constantBuffer.m_world };
    if (parentMesh != nullptr)
        constantBufferTemp.m_world = constantBufferTemp.m_world * parentMesh->GetWorldMatrix(); //это правильный порядок
    deviceContext->UpdateSubresource(d3dConstantBuffer, 0, nullptr, &constantBufferTemp, 0, 0);

    //DRAW
    deviceContext->DrawIndexedInstanced(indicesCount, 2, 0, 0, 0);

}