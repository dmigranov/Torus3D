//inspired by:
//https://www.3dgep.com/introduction-to-directx-11/#Initialize_DirectX

#include <pch.h>
#include "Game.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

// Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nCmdShow)
{
    Game& game = Game::GetInstance();
    game.InitializeEngine(hInstance, nCmdShow, L"Сф. и Элл. Пространства", false, false);
    //game.MoveCamera(Vector3(0, 0, -XM_PI / 4));
    game.SetCameraFovY(XM_PI / 2);
    game.SetBackgroundColor(DirectX::Colors::PowderBlue);
    Texture * earthTexture = game.CreateTexture(L"earth8k.dds");
    Texture * sviborgTexture = game.CreateTexture(L"sviborg.dds");
    Texture * fireTexture = game.CreateTexture(L"fire.dds");
    Texture * moonTexture = game.CreateTexture(L"moon.dds");
    Texture * asteroidTexture = game.CreateTexture(L"asteroid.dds");
    Texture * cubeTexture = game.CreateTexture(L"cubemap.dds");

    
    //auto earth = new SphericalSphere(0.999999, 35, 35, earthTexture, SphericalRotationYW(3 * XM_PI / 2));
    //auto earth = new SphericalSphere(0.92f, 35, 35, earthTexture, SphericalRotationYW(3 * XM_PI / 2));
    //game.AddMesh(earth);

    auto cube = new ToricCube(1., Matrix::CreateTranslation(0, 0, 2), cubeTexture);
    game.AddMesh(cube);
    cube->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
        return Matrix::CreateRotationY(delta) * in;
    }));



    auto controller = new ToricCube(0.5);
    controller->SetVisible(false);
    controller->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
        auto ks = Keyboard::Get().GetState();

        static int sceneNum = 0;
        static bool changed = false;

        if (ks.D0)
        {
            changed = true;
            sceneNum = 2;
        }
        else if (ks.D9)
        {
            changed = true;
            sceneNum = 3;
        }
        else if (ks.D8)
        {
            changed = true;
            sceneNum = 0;
        }

        if (changed)
        {
            switch (sceneNum)
            {
            case 0:
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            }

            changed = false;
        }

        return Matrix();
    }));

    //game.AddMesh(controller);


    return game.StartGame();


}
 