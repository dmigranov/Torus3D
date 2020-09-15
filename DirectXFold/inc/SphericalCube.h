#pragma once
#include "SphericalMesh.h"
class SphericalCube :
	public SphericalMesh
{
public:
	SphericalCube(double wSec);
	SphericalCube(double wSec, DirectX::XMMATRIX world);
	SphericalCube(double wSec, DirectX::XMFLOAT4* colors);
	SphericalCube(double wSec, DirectX::XMMATRIX world, DirectX::XMFLOAT4* colors);

	double GetSectionHeight();
	void SetSectionHeight(double h);

private:
	DirectX::XMFLOAT4 GenerateRandomColor();
	double m_sectionHeight;
};

