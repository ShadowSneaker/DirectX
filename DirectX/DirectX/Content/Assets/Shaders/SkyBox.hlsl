TextureCube Texture;
SamplerState Sampler;


cbuffer CBuffer
{
	matrix ViewMatrix;
	float4 DirectionalLight;
	float4 LightColour;
	float4 AmbiantLight;
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
	Output.Colour = Colour;
	Output.uv = Position.xyz;
	return Output;
}


float4 PShader(float4 Position : SV_POSITION, float4 Colour : COLOUR, float3 uv : UV) : SV_TARGET
{
	return Colour * Texture.Sample(Sampler, uv);
}