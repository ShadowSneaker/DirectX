#include "Renderer.h"
#include "Meshes/Primitives/Cube.h"
#include "Camera.h"
#include "Lighting/DirectionalLight.h"


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
	//memcpy(MS.pData, &Mesh->GetVertices(), sizeof(Mesh->GetVertices()[0]) * Mesh->GetVertexCount() + 4);
	memcpy(MS.pData, &Mesh->GetVertices()[0], sizeof(Mesh->GetVertices()[0]) * Mesh->GetVertices().size());
	//std::copy(Mesh->GetVertices().begin(), Mesh->GetVertices().end(), MS.pData);
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


	RETURN(Shader)
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


	

	uint VertexCount{ 0 };


	STexture* Texture;
	ID3D11Buffer* Buffer;
	ID3D11Buffer* VBuffer;
	for (uint i = 0; i < Objects.size(); ++i)
	{
		VertexCount += Objects[i]->GetVertexCount();

		Texture = Objects[i]->GetTexture();
		Buffer = Objects[i]->GetShader().ConstantBuffer;
		VBuffer = Objects[i]->GetShader().VertexBuffer;


		if (Raster) Raster->Release();
		if (RasterDepth) RasterDepth->Release();

		D3D11_RASTERIZER_DESC Rasterizer;
		ZeroMemory(&Rasterizer, sizeof(Rasterizer));
		Rasterizer.FillMode = D3D11_FILL_SOLID;
		Rasterizer.CullMode = (Objects[i]->InvertFaces) ? D3D11_CULL_FRONT : D3D11_CULL_BACK;
		Setup->GetDevice()->CreateRasterizerState(&Rasterizer, &Raster);

		D3D11_DEPTH_STENCIL_DESC DSDesc;
		ZeroMemory(&DSDesc, sizeof(DSDesc));
		DSDesc.DepthEnable = true;
		DSDesc.DepthWriteMask = (Objects[i]->InvertFaces) ? D3D11_DEPTH_WRITE_MASK_ZERO : D3D11_DEPTH_WRITE_MASK_ALL;
		DSDesc.DepthFunc = D3D11_COMPARISON_LESS;
		Setup->GetDevice()->CreateDepthStencilState(&DSDesc, &RasterDepth);



		SMatrix4 World;

		SMatrix4 Scale;
		SMatrix4 Rotation;
		SMatrix4 Position;

		Scale.SetScale(Objects[i]->Transform.GetWorldScale());
		Rotation.SetRotate(Objects[i]->Transform.GetWorldRotation());
		Position.SetTranslate(Objects[i]->Transform.GetWorldLocation());


		//Scale.SetScale(1.0f, 1.0f, 1.0f);
		//Rotation.SetRotate(TO_RADIAN(0.0f), TO_RADIAN(0.0f), TO_RADIAN(0.0f));
		//Position.SetTranslate(0.0f, 0.0f, 5.0f);


		World = Scale * Rotation * Position;

		SMatrix4 View;
		SMatrix4 Projection;
		
		
		if (SelectedCamera)
		{
			View = SelectedCamera->GetViewMatrix();
		}
		else
		{
			View.Identity();
		}

		SVector2i Size = Window->GetWindowSize();
		//World.SetTranslate(0.0f, 0.0f, 5.0f);
		Projection = SMatrix4::PersepctiveFovLH(TO_RADIAN(45.0f), (float)Size[X] / (float)Size[Y], 0.0001f, 1000.0f);

		


		SVector4 Rot{ DirectionalLight->Transform.Rotation.GetAsVector() };

		
		SMatrix4 Transpose{ SMatrix4::Transpose(World) };

		if (Objects[i]->Reflect)
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
		

		// Not sure if it's a good idea to have this here, however, by putting this here I am able to change the colour of objects during runtime.

		//SVertex* Vertices = Objects[i]->GetVertices();
		std::vector<SVertex> Vertices = Objects[i]->GetVertices();
		uint VertexCount = Objects[i]->GetVertexCount();

		D3D11_MAPPED_SUBRESOURCE MS;
		Setup->GetDeviceContext()->Map(VBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &MS);
		//memcpy(MS.pData, &Objects[i]->GetVertices(), sizeof(Objects[i]->GetVertices()[0]) * Objects[i]->GetVertexCount());
		memcpy(MS.pData, &Objects[i]->GetVertices()[0], sizeof(Objects[i]->GetVertices()[0])* Objects[i]->GetVertices().size());

		Setup->GetDeviceContext()->Unmap(VBuffer, NULL);


		
		Setup->GetDeviceContext()->VSSetConstantBuffers(0, 1, &Buffer);
	
		//uint Stride = sizeof(SModelVertex);
		uint Stride = sizeof(SVertex);
		uint Offset = 0;

		Setup->GetDeviceContext()->IASetInputLayout(Objects[i]->GetShader().InputLayout);
		Setup->GetDeviceContext()->VSSetShader(Objects[i]->GetShader().VertexShader, 0, 0);
		Setup->GetDeviceContext()->PSSetShader(Objects[i]->GetShader().PixelShader, 0, 0);
		Setup->GetDeviceContext()->IASetVertexBuffers(0, 1, &VBuffer, &Stride, &Offset);
		Setup->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Setup->GetDeviceContext()->PSSetSamplers(0, 1, &Sampler);
		Setup->GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);
		Setup->GetDeviceContext()->RSSetState(Raster);
		Setup->GetDeviceContext()->OMSetDepthStencilState(RasterDepth, 0);
	
		Setup->GetDeviceContext()->Draw(Objects[i]->GetVertexCount(), 0);
	}

	//Setup->GetDeviceContext()->Draw(VertexCount, 0);
	Setup->GetSwapChain()->Present(0, 0);
}