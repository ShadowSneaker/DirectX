cbuffer CBuffer
{
	matrix ViewMatrix;
	float RedFactor;
	float Scale;
	float2 Packing;
}


struct VOut
{
	float4 Position : SV_POSITION;
	float4 Colour : COLOUR;
};


VOut VShader(float4 Position : POSITION, float4 Colour : COLOUR)
{
	VOut Output;
	Colour.r *= RedFactor;
	Output.Position = mul(ViewMatrix, Position);
	Output.Colour = Colour;
	return Output;
}


float4 PShader(float4 Position : SV_POSITION, float4 Colour : COLOUR) : SV_TARGET
{
	return Colour;
}