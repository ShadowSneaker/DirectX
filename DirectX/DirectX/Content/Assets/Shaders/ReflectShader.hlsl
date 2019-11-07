TextureCube Texture;
SamplerState Sampler;


cbuffer CBuffer
{
	matrix ViewMatrix;
	matrix WorldMatrix;
}


struct VOut
{
	float4 Position : SV_POSITION;
	float4 Colour : COLOUR;
	float3 uv : UV;
};


VOut VShader(float4 Position : POSITION, float4 Colour : COLOUR, float3 uv : UV, float3 Normal : NORMAL)
{
	VOut Output;
	Output.Position = mul(ViewMatrix, Position);
	Output.Colour = Colour * 0.5f;

	float3 WVPos = mul(WorldMatrix, Position);
	float3 WVNormal = mul(WorldMatrix, Normal);
	float3 Eyer = -normalize(WVPos);
	Output.uv = 2.0f * dot(Eyer, WVNormal) * WVNormal - Eyer;

	return Output;
}


float4 PShader(float4 Position : SV_POSITION, float4 Colour : COLOUR, float3 uv : UV) : SV_TARGET
{
	return Colour * Texture.Sample(Sampler, uv);
}