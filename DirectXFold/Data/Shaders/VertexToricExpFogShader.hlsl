#define IDENTITY_MATRIX float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)

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
	float3 instancePosition : TEXCOORD1; //TEXCOORD1 - просто семантика, ничего не занчит
};


struct VertexShaderOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD0;
	float fogFactor : FOG_FACTOR;
};

float4x4 translate(float4x4 m, float3 v)
{
	float x = v.x, y = v.y, z = v.z;
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
	return m;
}

//entry point
VertexShaderOutput main(VertexShaderInput IN/*, uint instanceID : SV_InstanceID*/)
{
	VertexShaderOutput OUT;

	matrix viewWorld;

	matrix instanceTranslation = translate(IDENTITY_MATRIX, IN.instancePosition);
	matrix resWorld =  mul(worldMatrix, instanceTranslation);
	viewWorld = mul(viewMatrix, resWorld);
	
	float4 cameraSpacePosition = mul(viewWorld, IN.position);
	float eucDistance = distance(float4(0, 0, 0, 1), cameraSpacePosition); //длина хорды

	OUT.color = IN.color;
	OUT.position = mul(projectionMatrix, cameraSpacePosition);;
	OUT.tex = IN.tex;

	//OUT.fogFactor = saturate(exp(-density * eucDistance));
	OUT.fogFactor = 1;
	
	return OUT;
}