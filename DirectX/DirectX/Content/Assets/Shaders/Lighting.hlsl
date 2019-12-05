#include "HelperFX/LightHelper.fx"


cbuffer CBPerFrame
{
	SDirectionalLight DirectionalLight;
	SPointLight PointLight;
	SSpotLight SpotLight;
	float3 EyePosW;
};


cbuffer CBPerObject
{
	float4x4 World;
	float4x4 WorldInvTranspose;
	float4x4 WorldViewProj;
	SMaterial Material;
};


struct SVertexIn
{
	float3 Position : POSITION;
	float3 NormalL : NORMAL;
};


struct SVertexOut
{
	float4 PositionH : SV_POSITION;
	float3 PositionW : POSITION;
	float3 NormalW : NORMAL;
};


SVertexOut VS(SVertexIn Vertex)
{
	SVertexOut VOut;

	// Transform the world space to space.
	VOut.PositionW = mul(Vertex.NormalL, (float3x3)WorldInvTranspose);

	// Transform to homogeneous clip space.
	VOut.PositionH = mul(float4(Vertex.Position, 1.0f), WorldViewProj);
	
	return VOut;
}


float4 PS(SVertexOut PIn) : SV_TARGET
{
	// Interpolating normal can unnormalize it, so normalize it.
	PIn.NormalW = normalize(PIn.NormalW);
	float3 ToEye = normalize(EyePosW - PIn.PositionW);

	// Start with a sum of zero.
	float4 Ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 Diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 Specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Sum the light contribution from each light source.
	float4 A, D, S;

	CalculateDirectionalLight(Material, DirectionalLight, PIn.NormalW, ToEye, A, D, S);
	Ambient += A;
	Diffuse += D;
	Specular += S;

	CalculatePointLight(Material, PointLight, PIn.PositionW, PIn.NormalW, ToEye, A, D, S);
	Ambient += A;
	Diffuse += D;
	Specular += S;

	CalculateSpotLight(Material, SpotLight, PIn.PositionW, PIn.NormalW, ToEye, A, D, S);
	Ambient += A;
	Diffuse += D;
	Specular += S;

	float4 LitColour = Ambient + Diffuse + Specular;

	// Common to take alpha from diffuse material.
	LitColour.a = Material.Diffuse.a;

	return LitColour;
}


technique11 LightTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}