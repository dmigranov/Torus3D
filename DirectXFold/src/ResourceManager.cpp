#include "pch.h"
#include "ResourceManager.h"
#include "..\inc\ResourceManager.h"

Texture* ResourceManager::CreateTexture(const WCHAR* name)
{
    auto texture = new Texture();
    if (!texture->Initialize(g_d3dDevice, name))
        return nullptr;
    textures.push_back(texture);
    return texture;
}
