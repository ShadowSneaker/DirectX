cbuffer CB0
{
	matrix WorldMatrix;
};


Texture2D Texture;
SamplerState Sampler;


struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};


VOut ModelVS(float4 position : POSITION, float2 texcoord : TEXCOORD, float3 normal : NORMAL)
{
	VOut output;
	float4 DefaultColour = { 1.0f, 1.0f, 1.0f, 1.0f };
	output.position = mul(WorldMatrix, position);
	output.texcoord = texcoord;
	output.color = DefaultColour;

	return output;
}


float4 ModelPS(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
	return Texture.Sample(Sampler, texcoord) * color;
}