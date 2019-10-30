struct VOut
{
	float4 Position : SV_POSITION;
	float4 Colour : COLOUR;
};


VOut VShader(float4 Position : POSITION, float4 Colour : COLOUR)
{
	VOut Output;
	Output.Position = Position;
	Output.Colour = Colour;
	return Output;
}


float4 PShader(float4 Position : SV_POSITION, float4 Colour : COLOUR) : SV_TARGET
{
	return Colour;
}