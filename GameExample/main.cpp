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
    Texture * gunTexture = game.CreateTexture(L"gun.dds");

    auto camera =(std::static_pointer_cast<SphericalCamera>(game.GetCamera()));
    camera->Move(Vector3(-0.5, 0, 0));

    /*int bodyCount = 8;
    for (int i = 0; i < bodyCount; i++)
    {
        auto mesh = new SphericalSphere(0.03f, 19, 20, earthTexture, SphericalRotationXW(i * XM_PI /bodyCount));
        mesh->AddUpdater(Mesh::MeshUpdater([&game, i](Matrix in, float delta) {
            return SphericalRotationYW(0.001*sin(delta * i / 500)) * in;
        }));
        game.AddMesh(mesh);
    }*/

    

    /*int bodyCount = 8;
    for (int i = 0; i < bodyCount; i++)
    {
        auto mesh = new SphericalSphere(0.15f, 20, 20, earthTexture, SphericalRotationXW(i * XM_PI / bodyCount));
        mesh->AddUpdater(Mesh::MeshUpdater([&game](Matrix in, float delta) {
            return in * SphericalRotationXW(-delta/7);
        }));
        game.AddMesh(mesh);
    }*/


    auto earth = new SphericalSphere(0.92f, 35, 35, earthTexture, SphericalRotationYW(3 * XM_PI / 2));
    game.AddMesh(earth);

    /*auto moon = new SphericalSphere(0.3f, 20, 20, moonTexture, SphericalRotationXW(XM_PI / 2) * SphericalRotationYW(XM_PI / 2) );
    moon->SetParent(earth);
    moon->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta ) {
        return in * SphericalRotationXZ(delta);
    }));
    game.AddMesh(moon);


    auto asteroid = new SphericalSphere(0.06f, 20, 20, asteroidTexture, SphericalRotationZW(-0.6f));
    asteroid->SetParent(moon);
    asteroid->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
        return in * SphericalRotationXZ(delta);
    }));
    game.AddMesh(asteroid);*/



    {
        auto head1 = new SphericalSphere(0.08f, 20, 20, sviborgTexture);
        head1->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            auto ks = Keyboard::Get().GetState();

            static double time = 0;
            if (!ks.LeftControl)
                time += delta;

            return SphericalRotationXZ(XM_PI / 2) * SphericalRotationZW(time / 5.) * SphericalRotationYW(0.1 * sin(time));

        }));
        game.AddMesh(head1);

        auto tail1 = new SphericalSphere(0.08f, 20, 20, gunTexture, SphericalRotationXW(0.16));
        tail1->SetParent(head1);
        game.AddMesh(tail1);

        int sect = 8;
        for (int i = 0; i < sect; i++)
        {
            Mesh* mesh = new SphericalSphere(0.01f, 20, 20, fireTexture, SphericalRotationYW(-0.12f) * SphericalRotationYZ(i * XM_2PI / sect));
            mesh->AddUpdater(SphericalMesh::MeshUpdater([i](Matrix in, float delta) {
                return  in * SphericalRotationYZ(delta / 3.f);
            }));
            mesh->SetParent(head1);
            game.AddMesh(mesh);
        }


        auto head2 = new SphericalSphere(0.08f, 20, 20, sviborgTexture);
        head2->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            auto ks = Keyboard::Get().GetState();

            static double time = 0;
            if (!ks.LeftControl)
                time += delta;

            return SphericalRotationXZ(XM_PI / 2) * SphericalRotationZW(time / 5.) * SphericalRotationYW(0.1 * sin(time)) * SphericalRotationXZ(XM_PI / 2 - 0.3) * SphericalRotationZW(0.4);

        }));
        game.AddMesh(head2);

        auto tail2 = new SphericalSphere(0.08f, 20, 20, gunTexture, SphericalRotationXW(0.16));
        tail2->SetParent(head2);
        game.AddMesh(tail2);

        for (int i = 0; i < sect; i++)
        {
            Mesh* mesh = new SphericalSphere(0.01f, 20, 20, fireTexture, SphericalRotationYW(-0.12f) * SphericalRotationYZ(i * XM_2PI / sect));
            mesh->AddUpdater(SphericalMesh::MeshUpdater([i](Matrix in, float delta) {
                return  in * SphericalRotationYZ(delta / 3.f);
            }));
            mesh->SetParent(head2);
            game.AddMesh(mesh);
        }
    }


    XMFLOAT4 colors[] = { XMFLOAT4(0, 1, 0, 1), XMFLOAT4(1, 1, 0, 1), XMFLOAT4(1, 0, 0, 1), XMFLOAT4(1, 0, 1, 1),
                        XMFLOAT4(0, 1, 0, 1) , XMFLOAT4(1, 1, 0, 1) , XMFLOAT4(1, 0, 0, 1) , XMFLOAT4(1, 0, 1, 1) };
    auto cube = new SphericalCube(0.96, SphericalRotationXW(0.3), colors);
    cube->AddUpdater(SphericalMesh::MeshUpdater([cube](Matrix in, float delta) {        
        auto ks = Keyboard::Get().GetState();

        static double time = 0;
        if (!ks.LeftControl)
            time += delta;
        else
            return (Matrix)in;

        double newSectionHeight = (sin(3 * time) + 16)/17;
        cube->SetSectionHeight(newSectionHeight);

        return SphericalRotationXZ(2 * delta) * (Matrix)cube->GetWorldMatrix();
    }));
    game.AddMesh(cube);
       
    
    /*auto gun = new SphericalEllipsoid(0.05, 0.05, 0.15, 20, 20, gunTexture);
    //auto bullet = new SphericalSphere(0.05, 5, 5, gunTexture);

    gun->AddUpdater(SphericalMesh::MeshUpdater([camera](Matrix, float) {
        auto ms = Mouse::Get().GetState();
        if (ms.rightButton)
            std::cout << "hello";

        return SphericalRotationXW(0.15) * SphericalRotationYW(-0.15) * SphericalRotationZW(0.2) * ((Matrix)camera->GetView()).Transpose();
    }));
    game.AddMesh(gun);*/


    return game.StartGame();

}
    
    /*{
        game.MoveCamera(Vector3(0, 0, -XM_PI / 4));
        game.SetCameraFovY(XM_PI / 2);
        game.SetBackgroundColor(DirectX::Colors::PowderBlue);

        auto earthTexture = game.CreateTexture(L"earth.dds");
        auto asteroidTexture = game.CreateTexture(L"asteroid2.dds");
        auto fabricTexture = game.CreateTexture(L"fabric.dds");
        auto sviborgTexture = game.CreateTexture(L"sviborg.dds");
        auto fireTexture = game.CreateTexture(L"fire.dds");
        auto moonTexture = game.CreateTexture(L"moon.dds");
        if (!earthTexture || !moonTexture || !asteroidTexture || !fireTexture || !sviborgTexture || !fabricTexture)
        {
            MessageBox(nullptr, TEXT("Failed to load textures."), TEXT("Error"), MB_OK);
            return 1;
        }

        auto mesh1 = new SphericalSphere(0.15f, 20, 20, earthTexture);
        //auto mesh1 = new SphericalEllipsoid(0.9999f, 0.55f, 0.45f, 40, 40, asteroidTexture);

        mesh1->AddUpdater(Mesh::MeshUpdater([&game](Matrix in, float delta) {
            auto ks = Keyboard::Get().GetState();
            float gain = 0.045f;
            Matrix m = Matrix::Identity;
            if (ks.U)
                m = SphericalRotationYW(-gain);
            if (ks.J)
                m = SphericalRotationYW(gain);
            if (ks.H)
                m = SphericalRotationXW(gain);
            if (ks.K)
                m = SphericalRotationXW(-gain);
            return  in *  m;  //так всегда вверх!
        }));
        game.AddMesh(mesh1);


        for (int i = 1; i < 8; i++)
        {
            Mesh* mesh = new SphericalSphere(0.15f, 20, 20, earthTexture, SphericalRotationZW(i * XM_PI / 8));
            game.AddMesh(mesh);
        }


        auto moon = new SphericalSphere(0.05f, 20, 20, moonTexture, SphericalRotationZW(-0.39f));
        moon->SetParent(mesh1);
        moon->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            return in * SphericalRotationXZ(delta);
        }));
        game.AddMesh(moon);


        auto asteroid = new SphericalSphere(0.02f, 20, 20, asteroidTexture, SphericalRotationZW(-0.1f));
        asteroid->SetParent(moon);
        asteroid->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            return in * SphericalRotationXZ(7 * delta);
        }));
        game.AddMesh(asteroid);
        
        
        auto head = new SphericalSphere(0.08f, 20, 20, sviborgTexture);
        head->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            auto ks = Keyboard::Get().GetState();

            static double time = 0;
            if (!ks.Space)
                time += delta;

            return SphericalRotationYW(-0.15f) * SphericalRotationXZ(XM_PI / 2) * SphericalRotationZW(time / 5.) * SphericalRotationYW(0.03 * sin(7 * time));

        }));
        game.AddMesh(head);

        int sect = 8;
        for (int i = 0; i < sect; i++)
        {
            Mesh* mesh = new SphericalSphere(0.01f, 20, 20, fireTexture, SphericalRotationYW(-0.12f) * SphericalRotationYZ(i * XM_2PI / sect));
            mesh->AddUpdater(SphericalMesh::MeshUpdater([i](Matrix in, float delta) {
                return  in * SphericalRotationYZ(delta / 3.f);
            }));
            mesh->SetParent(head);
            game.AddMesh(mesh);
        }
        

        auto mesh2 = SphericalMeshLoader::LoadMesh("mesh3.sph");
        mesh2->SetTexture(fabricTexture);
        mesh2->SetWorldMatrix(SphericalRotationYZ(XM_PIDIV2) * SphericalRotationYW(0.09f));
        game.AddMesh(mesh2);
        
    }*/

