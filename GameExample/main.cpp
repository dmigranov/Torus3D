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
    Texture * sunTexture = game.CreateTexture(L"8k_sun.dds");

    
    auto earth = new SphericalSphere(0.92f, 35, 35, earthTexture, SphericalRotationYW(3 * XM_PI / 2));
    game.AddMesh(earth);
    
        auto head1 = new SphericalSphere(0.08f, 20, 20, asteroidTexture);
        head1->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            auto ks = Keyboard::Get().GetState();

            static double time = 0;
            if (!ks.LeftControl)
                time += delta;

            return SphericalRotationXZ(XM_PI / 2) * SphericalRotationZW(time / 5.) * SphericalRotationYW(0.1 * sin(time));

        }));
        game.AddMesh(head1);
        head1->SetVisible(false);


        auto tail1 = new SphericalSphere(0.08f, 20, 20, asteroidTexture, SphericalRotationXW(0.16));
        tail1->SetParent(head1);
        tail1->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            auto ks = Keyboard::Get().GetState();

            static double time = 0;
            if (!ks.LeftControl)
                time += delta;

            return SphericalRotationXW(0.16) * SphericalRotationYW(0.02 * sin(time));
        }));
        game.AddMesh(tail1);
        tail1->SetVisible(false);

        auto tail2 = new SphericalSphere(0.08f, 20, 20, asteroidTexture, SphericalRotationXW(0.16));
        tail2->SetParent(tail1);
        tail2->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            auto ks = Keyboard::Get().GetState();

            static double time = 0;
            if (!ks.LeftControl)
                time += delta;

            return SphericalRotationXW(0.16) * SphericalRotationYW(0.03 * sin(time));
        }));
        game.AddMesh(tail2);
        tail2->SetVisible(false);

        int sect = 8;
        for (int i = 0; i < sect; i++)
        {
            Mesh* mesh = new SphericalSphere(0.01f, 20, 20, fireTexture, SphericalRotationYW(-0.12f) * SphericalRotationYZ(i * XM_2PI / sect));
            mesh->AddUpdater(SphericalMesh::MeshUpdater([i, head1, mesh](Matrix in, float delta) {
                mesh->SetVisible(head1->IsVisible());
                return  in * SphericalRotationYZ(delta / 3.f);
            }));
            mesh->SetParent(head1);
            game.AddMesh(mesh);
        }

        auto sun = new SphericalSphere(0.18f, 20, 20, sunTexture);
        sun->SetVisible(false);
        sun->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            auto ks = Keyboard::Get().GetState();

            static double time = 0;
            if (!ks.LeftControl)
                time += delta;


            return SphericalRotationXZ(-2 * time ) * SphericalRotationXZ(XM_PI / 2) * SphericalRotationZW(time / 5.) * SphericalRotationXZ(XM_PI / 2 - 0.3) * SphericalRotationZW(0.4) ;
        }));
        game.AddMesh(sun);

        auto sunEarth = new SphericalSphere(0.06f, 20, 20, earthTexture, SphericalRotationXY(-0.19f) * SphericalRotationXW(-0.31f) );
        sunEarth->SetParent(sun);
        sunEarth->SetVisible(false);
        sunEarth->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            return  SphericalRotationXZ(3.f * delta ) * in * SphericalRotationXZ( delta / 2.f);
        }));
        game.AddMesh(sunEarth);

        auto moon = new SphericalSphere(0.03f, 20, 20, moonTexture, SphericalRotationXW(-0.11f));
        moon->SetParent(sunEarth);
        moon->SetVisible(false);
        moon->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            return   SphericalRotationXZ(3.f * delta) * in * SphericalRotationXZ(delta / 2.f);
        }));
        game.AddMesh(moon);

    SphericalSphere** smallEarthes = new SphericalSphere*[8];

    int smallEarthesSect = 8;
    for (int i = 0; i < smallEarthesSect; i++)
    {
        smallEarthes[i] = new SphericalSphere(0.15f, 20, 20, earthTexture, SphericalRotationZW(XM_PIDIV2) * SphericalRotationZW(i * XM_PI / smallEarthesSect));
        smallEarthes[i]->SetVisible(false);
        game.AddMesh(smallEarthes[i]);
    }
    smallEarthes[0]->SetVisible(true);


    auto controller = new SphericalCube(0.96);
    controller->SetVisible(false);
    controller->AddUpdater(SphericalMesh::MeshUpdater([earth, head1, tail1, tail2, sun, sunEarth, moon,
        smallEarthes, smallEarthesSect](Matrix in, float delta) {
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
                head1->SetVisible(true);
                tail1->SetVisible(true);
                tail2->SetVisible(true);
                sun->SetVisible(true);
                sunEarth->SetVisible(true);
                moon->SetVisible(true);

                for(int i = 0; i < smallEarthesSect; i++)
                    smallEarthes[i]->SetVisible(false);

                break;
            case 2:
                head1->SetVisible(false);
                tail1->SetVisible(false);
                tail2->SetVisible(false);
                sun->SetVisible(false);
                sunEarth->SetVisible(false);
                moon->SetVisible(false);

                smallEarthes[0]->SetVisible(true);
                for (int i = 1; i < smallEarthesSect; i++)
                    smallEarthes[i]->SetVisible(false);

                break;
            case 3:
                head1->SetVisible(false);
                tail1->SetVisible(false);           
                tail2->SetVisible(false);
                sun->SetVisible(false);
                sunEarth->SetVisible(false);
                moon->SetVisible(false);

                for (int i = 0; i < smallEarthesSect; i++)
                    smallEarthes[i]->SetVisible(true);

                break;
            }

            changed = false;
        }


        return Matrix();
    }));

    game.AddMesh(controller);

    


    /*constexpr int smallEarthesSect = 64;

    SphericalSphere** smallEarthes = new SphericalSphere * [smallEarthesSect];

    for (int i = 0; i < smallEarthesSect; i++)
    {
        smallEarthes[i] = new SphericalSphere(0.03f, 20, 20, earthTexture, SphericalRotationZW(XM_PIDIV2) * SphericalRotationZW(i * XM_PI / smallEarthesSect));
        game.AddMesh(smallEarthes[i]);
    }*/

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

