Texture2D Texture;
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
	float2 uv : UV;
	float3 Normal : NORMAL;
};


VOut VShader(float4 Position : POSITION, float4 Colour : COLOUR, float2 uv : UV, float3 Normal : NORMAL)
{
	VOut Output;
	Output.Position = mul(ViewMatrix, Position);

	float DiffuseAmount = saturate(dot(Normal, -DirectionalLight));
	Output.Colour = (AmbiantLight + (LightColour * DiffuseAmount)) * Colour;

	Output.uv = uv;
	Output.Normal = Normal;
	return Output;
}


float4 PShader(float4 Position : SV_POSITION, float4 Colour : COLOUR, float2 uv : UV) : SV_TARGET
{
	return Colour * Texture.Sample(Sampler, uv);
}