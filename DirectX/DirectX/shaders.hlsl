Texture2D texture0;
SamplerState sampler0;


cbuffer CBuffer
{
	matrix Matrix;
	float4 DirectionalLight;
	float4 DirectionalLightColour;
	float4 AmbientLightColour;
};

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};


VOut VShader(float4 position : POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD, float3 normal : NORMAL)
{
	VOut output;

	output.position = mul(Matrix, position);

	float DiffuseAmount = dot(DirectionalLight, normal);
	DiffuseAmount = saturate(DiffuseAmount);
	output.color = AmbientLightColour + (DirectionalLightColour * DiffuseAmount);

	output.texcoord = texcoord;
	return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
	return color * texture0.Sample(sampler0, texcoord);
}