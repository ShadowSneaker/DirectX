Texture2D texture0;
SamplerState sampler0;


cbuffer CBuffer
{
	matrix Matrix;
	float RedFraction;
	float Scale;
	float2 Packing;
};

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};


VOut VShader(float4 position : POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD)
{
	VOut output;

	color.r *= RedFraction;
	output.position = mul(Matrix, position);
	output.color = color;
	output.texcoord = texcoord;

	return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
	return color * texture0.Sample(sampler0, texcoord);
}