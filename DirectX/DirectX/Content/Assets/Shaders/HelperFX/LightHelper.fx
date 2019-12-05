struct SMaterial
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Reflect;
};


struct SDirectionalLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Direction;
	float Pad;
};


struct SPointLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;

	float3 Position;
	float Range;

	float3 Att;
	float Pad;
};


struct SSpotLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;

	float3 Position;
	float Range;

	float3 Direction;
	float Spot;
	float3 Att;
	float Pad;
};


void CalculateDirectionalLight(SMaterial Material, SDirectionalLight Light, float3 Normal, float3 Eye, out float4 Ambient, out float4 Diffuse, out float4 Specular)
{
	Ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	Diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	Specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 LightVector = -Light.Direction;
	Ambient = Material.Ambient * Light.Ambient;
	float DiffuseFactor = dot(LightVector, Normal);

	[flatten]
	if (DiffuseFactor > 0.0f)
	{
		float3 V = reflect(-LightVector, Normal);
		float SpecFactor = pow(max(dot(V, Eye), 0.0f), Material.Specular.w);

		Diffuse = DiffuseFactor * Material.Diffuse * Light.Diffuse;
		Specular = SpecFactor * Material.Specular * Light.Specular;
	}
}


void CalculatePointLight(SMaterial Material, SPointLight Light, float3 Position, float3 Normal, float3 Eye, out float4 Ambient, out float4 Diffuse, out float4 Specular)
{
	Ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	Diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	Specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 LightVector = Light.Position - Position;
	float Distance = length(LightVector);

	if (Distance > Light.Range) return;

	LightVector /= Distance;
	Ambient = Material.Ambient * Light.Ambient;

	// Add diffuse and specular term, provided the surface is in the line of sight.
	float DiffuseFactor = dot(LightVector, Normal);

	[flatten]
	if (DiffuseFactor > 0.0f)
	{
		float3 V = reflect(-LightVector, Normal);
		float SpecFactor = pow(max(dot(V, Eye), 0.0f), Material.Specular.w);

		Diffuse = DiffuseFactor * Material.Diffuse * Light.Diffuse;
		Specular = SpecFactor * Material.Specular * Light.Specular;
	}

	// Attenuate
	float Att = 1.0f / dot(Light.Att, float3(1.0f, Distance, Distance * Distance));
	Diffuse *= Att;
	Specular *= Att;
}


void CalculateSpotLight(SMaterial Material, SSpotLight Light, float3 Position, float3 Normal, float3 Eye, out float4 Ambient, out float4 Diffuse, out float4 Specular)
{
	Ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	Diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	Specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 LightVector = Light.Position - Position;
	float Distance = length(LightVector);

	if (Distance > Light.Range) return;

	LightVector /= Distance;
	Ambient = Material.Ambient * Light.Ambient;

	float DiffuseFactor = dot(LightVector, Normal);

	[flatten]
	if (DiffuseFactor > 0.0f)
	{
		float3 V = reflect(-LightVector, Normal);
		float SpecFactor = pow(max(dot(V, Eye), 0.0f), Material.Specular.w);

		Diffuse = DiffuseFactor * Material.Diffuse * Light.Diffuse;
		Specular = SpecFactor * Material.Specular * Light.Specular;
	}

	// Scale by spotlight factor and attenuate.
	float Spot = pow(max(dot(-LightVector, Light.Direction), 0.0f), Light.Spot);
	float Att = Spot / dot(Light.Att, float3(1.0f, Distance, Distance * Distance));

	Ambient *= Spot;
	Diffuse *= Att;
	Specular *= Att;
}