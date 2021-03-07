#include "pch.h"
#include "ToricCube.h"

#include "Game.h"


using namespace DirectX::SimpleMath;
using namespace DirectX;

ToricCube::ToricCube(double sideLength) : ToricCube::ToricCube(sideLength, Matrix::Identity)
{ }

ToricCube::ToricCube(double sideLength, DirectX::SimpleMath::Matrix world) : ToricMesh()
{
    auto cubeCoord = sideLength / 2;
    auto color = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f); //todo
    ToricMesh::VertexPosColor vertices[] = {
        //front:
        { XMFLOAT4(-cubeCoord,  -cubeCoord, -cubeCoord, 1), color, XMFLOAT2(1.f/3, 1.f) }, // 0
        { XMFLOAT4(-cubeCoord,  cubeCoord, -cubeCoord, 1), color, XMFLOAT2(1.f / 3, 0.5f)  }, // 1
        { XMFLOAT4(cubeCoord,  -cubeCoord, -cubeCoord, 1), color, XMFLOAT2(2.f / 3, 1.f)   }, // 2
        { XMFLOAT4(cubeCoord,  cubeCoord, -cubeCoord, 1), color, XMFLOAT2(2.f / 3, 0.5f)  }, // 3

        //left:
        { XMFLOAT4(-cubeCoord,  -cubeCoord, -cubeCoord, 1), color, XMFLOAT2(2.f / 3, 0.5f) }, // 4
        { XMFLOAT4(-cubeCoord,  -cubeCoord, cubeCoord, 1), color,  XMFLOAT2(1.f / 3, 0.5f) }, // 5
        { XMFLOAT4(-cubeCoord,  cubeCoord, -cubeCoord, 1), color, XMFLOAT2(2.f / 3, 0.f)}, // 6
        { XMFLOAT4(-cubeCoord,  cubeCoord, cubeCoord, 1), color, XMFLOAT2(1.f / 3, 0.f)  }, // 7

        //right:
        { XMFLOAT4(cubeCoord,  -cubeCoord, -cubeCoord, 1), color, XMFLOAT2(0.f, 0.5f)   }, // 8
        { XMFLOAT4(cubeCoord,  cubeCoord, cubeCoord, 1), color, XMFLOAT2(1.f / 3, 0.f)   }, // 9
        { XMFLOAT4(cubeCoord,  -cubeCoord, cubeCoord, 1), color, XMFLOAT2(1.f / 3, 0.5f)  }, // 10
        { XMFLOAT4(cubeCoord,  cubeCoord, -cubeCoord, 1), color, XMFLOAT2(0.f, 0.f)  }, // 11

        //top:
        { XMFLOAT4(-cubeCoord,  cubeCoord, -cubeCoord, 1), color, XMFLOAT2(2.f / 3, 0.5f)  }, // 12
        { XMFLOAT4(-cubeCoord,  cubeCoord, cubeCoord, 1), color, XMFLOAT2(2.f / 3, 0.f)  }, // 13
        { XMFLOAT4(cubeCoord,  cubeCoord, cubeCoord, 1), color, XMFLOAT2(1.f, 0.f)   }, // 14
        { XMFLOAT4(cubeCoord,  cubeCoord, -cubeCoord, 1), color, XMFLOAT2(1.f, 0.5f)  }, // 15

        //bottom:
        { XMFLOAT4(-cubeCoord,  -cubeCoord, cubeCoord, 1), color, XMFLOAT2(0.f, 1.f)   }, // 16
        { XMFLOAT4(-cubeCoord,  -cubeCoord, -cubeCoord, 1), color, XMFLOAT2(0.f, 0.5f) }, // 17
        { XMFLOAT4(cubeCoord,  -cubeCoord, -cubeCoord, 1), color, XMFLOAT2(1.f / 3, 0.5f) }, // 18
        { XMFLOAT4(cubeCoord,  -cubeCoord, cubeCoord, 1), color, XMFLOAT2(1.f / 3, 1.f)  }, // 19

        //back:
        { XMFLOAT4(cubeCoord,  cubeCoord, cubeCoord, 1), color, XMFLOAT2(2.f / 3, 0.5f)  }, // 20
        { XMFLOAT4(-cubeCoord,  cubeCoord, cubeCoord, 1), color, XMFLOAT2(1.f, 0.5f)  }, // 21
        { XMFLOAT4(-cubeCoord,  -cubeCoord, cubeCoord, 1), color, XMFLOAT2(1.f, 1.f)  }, // 22
        { XMFLOAT4(cubeCoord,  -cubeCoord, cubeCoord, 1), color, XMFLOAT2(2.f / 3, 1.f)   }, // 23
    };
    g_Vertices = vertices;
    verticesCount = _countof(vertices);


    WORD indices[] = {
            0, 1, 2,
            2, 1, 3, //new!

            4, 5, 6,
            7, 6, 5, //new!

            8, 9, 10,
            8, 11, 9, //new!

            12, 13, 14,
            12, 14, 15, //new!

            16, 17, 18,
            16, 18, 19, //new!

            20, 21, 22,
            23, 20, 22 //new!
    };


    auto& game = Game::GetInstance();
    auto device = game.g_d3dDevice;
    deviceContext = game.g_d3dDeviceContext;
    d3dConstantBuffer = game.g_d3dVSConstantBuffers[2];
    g_Indices = indices;

    indicesCount = _countof(indices);

    // Create and initialize the vertex buffer.
    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;  //how the buffer is bound to pipeline
    vertexBufferDesc.ByteWidth = sizeof(VertexPosColor) * verticesCount;
    vertexBufferDesc.CPUAccessFlags = 0;    // no CPU access is necessary
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    //used to specify the data that is used to initialize a buffer when it is created.
    D3D11_SUBRESOURCE_DATA resourceData;
    ZeroMemory(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));
    resourceData.pSysMem = g_Vertices; //A pointer to the data to initialize the buffer with.

    device->CreateBuffer(&vertexBufferDesc, &resourceData, &g_d3dVertexBuffer);

    // Create and initialize the index buffer.
    D3D11_BUFFER_DESC indexBufferDesc;
    ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));

    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.ByteWidth = sizeof(WORD) * indicesCount;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    resourceData.pSysMem = g_Indices;

    device->CreateBuffer(&indexBufferDesc, &resourceData, &g_d3dIndexBuffer);

    constantBuffer.m_world = world;
}

ToricCube::ToricCube(double sideLength, Texture* texture) : ToricCube(sideLength, Matrix::Identity, texture)
{ }

ToricCube::ToricCube(double sideLength, Matrix world, Texture* texture) : ToricCube(sideLength, world)
{
    m_texture = texture;
}
