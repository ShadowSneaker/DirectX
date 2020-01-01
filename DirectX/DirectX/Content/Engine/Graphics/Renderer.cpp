#include "Renderer.h"
#include "Meshes/Primitives/Cube.h"
#include "Camera.h"
#include "Lighting/DirectionalLight.h"
#include "../Font/Font.h"
#include <DirectXMath.h>


CRenderer::CRenderer(HINSTANCE HandleInstance, int CommandShow)
{
	Window = new CWindow{ WindowName };
	if (FAILED(Window->InitialiseWindow(HandleInstance, CommandShow)))
	{
		exit(0);
	}

	Setup = new CDirectXSetup{ Window };

	if (FAILED(Setup->Initialise()))
	{
		exit(0);
	}


	// TEMP
	DirectionalLight = new CDirectionalLight{};

	// I don't like how the current setup of font is done. Currently I have to input the device and device context into
	// the font then call a draw method which is what draws it on the screen. I dislike this approach as I feel as if
	// components should not know how to draw themselves, but just have the nessissary information to draw themselves.
	// At which point the renderer gets that information then draws the text. 
	// Doing this also allows easy lists of fonts to go through the same procedure without the need to store duplicated functions in RAM.

	// For now, since there will only be one font on screen. It doesn't really matter how it is setup, so long as it is setup.
	ScoreText = new CFont{ "Content/Assets/Fonts/Font1.bmp", Setup->GetDevice(), Setup->GetDeviceContext() };
	ScoreText->Location = SVector2{ -1.0f, 1.0f };
	ScoreText->Size = 0.05f;
}


CRenderer::~CRenderer()
{
	//if (VertexBuffer) VertexBuffer->Release();

	DeleteAllMeshes();
	DeleteAllTextures();
	delete DirectionalLight; // temp delete.

	delete Setup;
	if (Sampler) Sampler->Release();
	delete Window;
}


void CRenderer::DeleteAllMeshes()
{
	while (!Objects.empty())
	{
		delete Objects[Objects.size() - 1];
		Objects.pop_back();
	}
}


void CRenderer::DeleteAllTextures()
{
	for (auto i = Textures.begin(); i != Textures.end(); ++i)
	{
		i->second->Release();
	}
	Textures.clear();
}


void CRenderer::UpdateObjects()
{
	SMatrix4 View;
	SMatrix4 Projection;

	float NearClip{ 0.0001f };
	float FarClip{ 1000.0f };
	float FOV{ 45.0f };
	if (SelectedCamera)
	{
		View = SelectedCamera->GetViewMatrix();
		NearClip = SelectedCamera->NearClipPlane;
		FarClip = SelectedCamera->FarClipPlane;
		float FOV = SelectedCamera->FieldOfView;
	}
	else
	{
		View.Identity();
	}

	SVector2i Size = Window->GetWindowSize();
	Projection = SMatrix4::PerspectiveFOV(TO_RADIAN(FOV), (float)Size[X] / (float)Size[Y], NearClip, FarClip);


	SVector4 Rot{ DirectionalLight->Transform.Rotation.GetAsVector() };


	// I do this to make sure I render the skybox first.
	// This is important as any object rendered before the skybox
	// will appear invisible. Although it will still block the sight of other objects
	// Instead it will create a "window" through the overlapped object.

	// For some reason with this it just does not draw any nealy created objects.
	// Without the skybox I can see the object and everything is fine.
	RenderObject(SkyBox, View, Projection, Rot);


	for (uint i = 0; i < Objects.size(); ++i)
	{
		if (Objects[i] != SkyBox)
		{
			RenderObject(Objects[i], View, Projection, Rot);
		}
	}
}


void CRenderer::UpdateLights() const
{
	ID3D11Buffer* Buffer;
	ID3D11Buffer* VBuffer;
	for (uint i = 0; i < Lights.size(); ++i)
	{
		Buffer = Lights[i]->GetShader().ConstantBuffer;
		VBuffer = Lights[i]->GetShader().VertexBuffer;


		SCBPerFrame PF;
		

		SCBPerObject PO;


		// Update the ps and vs here for each light.
		// In a new function for initiating the light, create the Pixel shader and Vertex shader using the new shader type.

		Setup->GetDeviceContext()->IASetInputLayout(Lights[i]->GetShader().InputLayout);
		Setup->GetDeviceContext()->VSSetShader(Lights[i]->GetShader().VertexShader, 0, 0);
		Setup->GetDeviceContext()->PSSetShader(Lights[i]->GetShader().PixelShader, 0, 0);
	}
}


void CRenderer::AddMesh(CStaticMesh* Mesh)
{
	if (Mesh)
	{
		Objects.push_back(Mesh);
	}
}


void CRenderer::RemoveMesh(CStaticMesh* Mesh)
{
	if (Mesh)
	{
		for (uint i = 0; i < Objects.size(); ++i)
		{
			if (Objects[i] == Mesh)
			{
				Objects.erase(Objects.begin() + i);
				return;
			}
		}
	}
}


void CRenderer::DeleteMesh(CStaticMesh* Mesh)
{
	if (Mesh)
	{
		RemoveMesh(Mesh);
		delete Mesh;
	}
}


void CRenderer::AddCamera(CCamera* Camera)
{
	if (Camera)
	{
		Cameras.push_back(Camera);
		if (Cameras.size() == 1)
		{
			SelectedCamera = Camera;
		}
	}
}


void CRenderer::RemoveCamera(CCamera* Camera)
{
	if (Camera)
	{
		for (uint i = 0; i < Cameras.size(); ++i)
		{
			if (Cameras[i] == Camera)
			{
				Cameras.erase(Cameras.begin() + i);
				return;
			}
		}
	}
}


void CRenderer::DeleteCamera(CCamera* Camera)
{
	if (Camera)
	{
		RemoveCamera(Camera);
		delete Camera;
	}
}


void CRenderer::AddLight(CLightBase* Light)
{
	if (Light)
	{
		Lights.push_back(Light);
	}
}


void CRenderer::RemoveLight(CLightBase* Light)
{
	if (Light)
	{
		for (uint i = 0; i < Lights.size(); ++i)
		{
			Lights.erase(Lights.begin() + i);
			return;
		}
	}
}


void CRenderer::DeleteLight(CLightBase* Light)
{
	if (Light)
	{
		RemoveLight(Light);
		delete Light;
	}
}


SShader CRenderer::SetShader(CStaticMesh* Mesh, std::string FilePath, bool UseDefaultPath)
{
	SFilePath File;
	if (UseDefaultPath)
	{
		File.FileName = FilePath;
		File.FilePath = TFileManager::ShaderFilePath;
	}
	else
	{
		File = SFilePath::GetFileName(FilePath);
	}
	

	HRESULT HR = S_OK;
	SShader Shader{};

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth = sizeof(Mesh->GetVertices()[0]) * Mesh->GetVertexCount();
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HR = Setup->GetDevice()->CreateBuffer(&BufferDesc, NULL, &Shader.VertexBuffer);
	if (FAILED(HR)) return Shader;


	D3D11_BUFFER_DESC CBuffer;
	ZeroMemory(&CBuffer, sizeof(CBuffer));
	CBuffer.Usage = D3D11_USAGE_DEFAULT;
	CBuffer.ByteWidth = 112;
	CBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HR = Setup->GetDevice()->CreateBuffer(&CBuffer, NULL, &Shader.ConstantBuffer);



	D3D11_MAPPED_SUBRESOURCE MS;
	Setup->GetDeviceContext()->Map(Shader.VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &MS);
	memcpy(MS.pData, &Mesh->GetVertices()[0], sizeof(Mesh->GetVertices()[0]) * Mesh->GetVertices().size());
	Setup->GetDeviceContext()->Unmap(Shader.VertexBuffer, NULL);


	ID3DBlob* VS;
	ID3DBlob* PS;
	ID3DBlob* Error;

	HR = D3DX11CompileFromFile(File.GetFilePath().c_str() , 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, &Error, 0);
	if (Error != 0)
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		Error->Release();
		if (FAILED(HR)) return Shader;
	}

	HR = D3DX11CompileFromFile(File.GetFilePath().c_str(), 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, &Error, 0);
	if (Error != 0)
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		Error->Release();
		if (FAILED(HR)) return Shader;
	}

	HR = Setup->GetDevice()->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &Shader.VertexShader);
	if (FAILED(HR)) return Shader;

	HR = Setup->GetDevice()->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &Shader.PixelShader);
	if (FAILED(HR)) return Shader;

	Setup->GetDeviceContext()->VSSetShader(Shader.VertexShader, 0, 0);
	Setup->GetDeviceContext()->PSSetShader(Shader.PixelShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC IEDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOUR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	HR = Setup->GetDevice()->CreateInputLayout(IEDesc, ARRAYSIZE(IEDesc), VS->GetBufferPointer(), VS->GetBufferSize(), &Shader.InputLayout);
	if (FAILED(HR)) return Shader;

	Setup->GetDeviceContext()->IASetInputLayout(Shader.InputLayout);

	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	Setup->GetDevice()->CreateSamplerState(&SamplerDesc, &Sampler);


	return Shader;
}


SShader CRenderer::SetLightShader(CLightBase* Light, std::string FilePath, bool UseDefaultPath)
{
	SFilePath File;
	if (UseDefaultPath)
	{
		File.FileName = FilePath;
		File.FilePath = TFileManager::ShaderFilePath;
	}
	else
	{
		File = SFilePath::GetFileName(FilePath);
	}


	HRESULT HR = S_OK;
	SShader Shader{};

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth = 0;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HR = Setup->GetDevice()->CreateBuffer(&BufferDesc, NULL, &Shader.VertexBuffer);
	if (FAILED(HR)) return Shader;


	D3D11_BUFFER_DESC CBuffer;
	ZeroMemory(&CBuffer, sizeof(CBuffer));
	CBuffer.Usage = D3D11_USAGE_DEFAULT;
	CBuffer.ByteWidth = 112;
	CBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HR = Setup->GetDevice()->CreateBuffer(&CBuffer, NULL, &Shader.ConstantBuffer);



	D3D11_MAPPED_SUBRESOURCE MS;
	Setup->GetDeviceContext()->Map(Shader.VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &MS);
	//memcpy(MS.pData, &Mesh->GetVertices()[0], sizeof(Mesh->GetVertices()[0]) * Mesh->GetVertices().size());
	Setup->GetDeviceContext()->Unmap(Shader.VertexBuffer, NULL);


	ID3DBlob* VS;
	ID3DBlob* PS;
	ID3DBlob* Error;

	HR = D3DX11CompileFromFile(File.GetFilePath().c_str(), 0, 0, "VS", "vs_5_0", 0, 0, 0, &VS, &Error, 0);
	if (Error != 0)
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		Error->Release();
		if (FAILED(HR)) return Shader;
	}

	HR = D3DX11CompileFromFile(File.GetFilePath().c_str(), 0, 0, "PS", "ps_5_0", 0, 0, 0, &PS, &Error, 0);
	if (Error != 0)
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		Error->Release();
		if (FAILED(HR)) return Shader;
	}

	HR = Setup->GetDevice()->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &Shader.VertexShader);
	if (FAILED(HR)) return Shader;

	HR = Setup->GetDevice()->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &Shader.PixelShader);
	if (FAILED(HR)) return Shader;

	Setup->GetDeviceContext()->VSSetShader(Shader.VertexShader, 0, 0);
	Setup->GetDeviceContext()->PSSetShader(Shader.PixelShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC IEDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOUR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	HR = Setup->GetDevice()->CreateInputLayout(IEDesc, ARRAYSIZE(IEDesc), VS->GetBufferPointer(), VS->GetBufferSize(), &Shader.InputLayout);
	if (FAILED(HR)) return Shader;

	Setup->GetDeviceContext()->IASetInputLayout(Shader.InputLayout);

	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	Setup->GetDevice()->CreateSamplerState(&SamplerDesc, &Sampler);


	return Shader;
}


STexture* CRenderer::SetTexture(std::string FilePath, bool UseDefaultPath)
{
	SFilePath File;
	if (UseDefaultPath)
	{
		File.FileName = FilePath;
		File.FilePath = TFileManager::TextureFilePath;
	}
	else
	{
		File = SFilePath::GetFileName(FilePath);
	}


	if (!Textures.count(File.GetFilePath()))
	{
		if (!AddTexture(File)) return nullptr;
	}

	return Textures[File.GetFilePath()];
}


bool CRenderer::AddTexture(SFilePath File)
{
	if (!Textures.count(File.GetFilePath()))
	{
		HRESULT HR;
		STexture* NewTexture;

		HR = D3DX11CreateShaderResourceViewFromFile(Setup->GetDevice(), File.GetFilePath().c_str(), NULL, NULL, &NewTexture, NULL);
		if (FAILED(HR)) return false;

		Textures.insert(std::pair<std::string, STexture*>(File.GetFilePath(), NewTexture));
		return true;
	}

	return false;
}


void CRenderer::DrawAll()
{
	Setup->ClearView();
	UpdateObjects();
	UpdateLights();
	ScoreText->RenderText();

	Setup->GetSwapChain()->Present(0, 0);
}


void CRenderer::RenderObject(CStaticMesh* Mesh, SMatrix4 View, SMatrix4 Projection, SVector4 Rot)
{
	STexture* Texture;
	ID3D11Buffer* Buffer;
	ID3D11Buffer* VBuffer;

	Texture = Mesh->GetTexture();
	Buffer = Mesh->GetShader().ConstantBuffer;
	VBuffer = Mesh->GetShader().VertexBuffer;


	if (Raster) Raster->Release();
	if (RasterDepth) RasterDepth->Release();

	D3D11_RASTERIZER_DESC Rasterizer;
	ZeroMemory(&Rasterizer, sizeof(Rasterizer));
	Rasterizer.FillMode = D3D11_FILL_SOLID;
	Rasterizer.CullMode = (Mesh->InvertFaces) ? D3D11_CULL_FRONT : D3D11_CULL_BACK;
	Setup->GetDevice()->CreateRasterizerState(&Rasterizer, &Raster);

	D3D11_DEPTH_STENCIL_DESC DSDesc;
	ZeroMemory(&DSDesc, sizeof(DSDesc));
	DSDesc.DepthEnable = true;
	DSDesc.DepthWriteMask = (Mesh->InvertFaces) ? D3D11_DEPTH_WRITE_MASK_ZERO : D3D11_DEPTH_WRITE_MASK_ALL;
	DSDesc.DepthFunc = D3D11_COMPARISON_LESS;
	Setup->GetDevice()->CreateDepthStencilState(&DSDesc, &RasterDepth);


	SMatrix4 World = SMatrix4::GetWorldTransform(Mesh->Transform);
	


	SMatrix4 Transpose{ SMatrix4::Transpose(World) };

	if (Mesh->Reflect)
	{
		SReflectBuffer RBValues;
		RBValues.WorldMatrix = World * View;
		RBValues.ViewMatrix = World * View * Projection;
		Setup->GetDeviceContext()->UpdateSubresource(Buffer, 0, 0, &RBValues, 0, 0);

	}
	else
	{
		SCBuffer CBValues;
		CBValues.LightColour = DirectionalLight->Colour * DirectionalLight->Strength;
		CBValues.AmbiantLight = AmbiantColour * AmbiantLightStregth;
		CBValues.DirectionalLight = Transpose.VectorTransform(Rot);
		CBValues.DirectionalLight = Rot.Normalize();


		CBValues.ViewMatrix = World * View * Projection;
		Setup->GetDeviceContext()->UpdateSubresource(Buffer, 0, 0, &CBValues, 0, 0);
	}

	/*D3D11_MAPPED_SUBRESOURCE MS;
	Setup->GetDeviceContext()->Map(VBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &MS);
	//memcpy(MS.pData, &Objects[i]->GetVertices(), sizeof(Objects[i]->GetVertices()[0]) * Objects[i]->GetVertexCount());
	memcpy(MS.pData, &Mesh->GetVertices()[0], sizeof(Mesh->GetVertices()[0]) * Mesh->GetVertices().size());

	Setup->GetDeviceContext()->Unmap(VBuffer, NULL);*/



	Setup->GetDeviceContext()->VSSetConstantBuffers(0, 1, &Buffer);

	uint Stride = sizeof(SVertex);
	uint Offset = 0;

	Setup->GetDeviceContext()->IASetInputLayout(Mesh->GetShader().InputLayout);
	Setup->GetDeviceContext()->VSSetShader(Mesh->GetShader().VertexShader, 0, 0);
	Setup->GetDeviceContext()->PSSetShader(Mesh->GetShader().PixelShader, 0, 0);
	Setup->GetDeviceContext()->IASetVertexBuffers(0, 1, &VBuffer, &Stride, &Offset);
	//Setup->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Setup->GetDeviceContext()->PSSetSamplers(0, 1, &Sampler);
	Setup->GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);
	Setup->GetDeviceContext()->RSSetState(Raster);
	Setup->GetDeviceContext()->OMSetDepthStencilState(RasterDepth, 0);
	
	Setup->GetDeviceContext()->Draw(Mesh->GetVertexCount(), 0);
}