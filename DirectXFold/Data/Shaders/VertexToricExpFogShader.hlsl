cbuffer PerApplication : register(b0)
{
	matrix projectionMatrix;
	float density;
}

cbuffer PerFrame : register(b1)
{
	matrix viewMatrix;
}

cbuffer PerObject : register(b2)
{
	matrix worldMatrix;
}


//POSITION and COLOR are semantics that are used to link vs variables to ps variables
struct VertexShaderInput
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD0;
};

struct VertexShaderOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD0;
	float fogFactor : FOG_FACTOR;
};

//entry point
VertexShaderOutput main(VertexShaderInput IN, uint instanceID : SV_InstanceID)
{
	VertexShaderOutput OUT;
 

	matrix viewWorld;
	viewWorld = mul(viewMatrix, worldMatrix);
	
	float4 cameraSpacePosition = mul(viewWorld, IN.position);
	float eucDistance = distance(float4(0, 0, 0, 1), cameraSpacePosition); //����� �����
	//todo: ���� ������� �����, �������� ��������...

	OUT.color = IN.color;
	OUT.position = mul(projectionMatrix, cameraSpacePosition);
	OUT.tex = IN.tex;

	OUT.fogFactor = saturate(exp(-density * eucDistance));
	
	return OUT;
}