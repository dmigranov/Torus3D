#pragma once
#include "ToricMesh.h"

//� ����� ������ Mesh ������ ���� ����� ��� ��������� ������ � �����������,
//������� � ������� ����������!
class ToricCube :
    public ToricMesh
{
public:
	ToricCube(double sideLength);
	ToricCube(double sideLength, DirectX::SimpleMath::Matrix world);


};

