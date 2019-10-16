cbuffer CBuffer
{
	matrix WorldMatrix;
};


struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 textcoord : TEXCOORD;
};


VOut ModelVS(float4 position : POSITION, float2 textcoord : TEXCOORD, float3 normal : NORMAL)
{
	VOut output;
	float4 DefaultColour = { 1.0f, 1.0f, 1.0f, 1.0f };
	output.position = mul(WorldMatrix, position);
	output.texcoord
}