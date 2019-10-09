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
};


VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
	VOut output;

	color.r *= RedFraction;
	output.position = mul(Matrix, position);
	output.color = color;

	return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	return color;
}