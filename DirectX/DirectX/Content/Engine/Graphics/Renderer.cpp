#include "Renderer.h"
#include "Meshes/Primitives/Cube.h"


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

	if (FAILED(Initialise()))
	{
		exit(0);
	}
}


CRenderer::~CRenderer()
{
	
}


HRESULT CRenderer::Initialise()
{
	//AddCluster(new CCube{ this }, "Shaders.hlsl");
	//CCube* Cube = new CCube{ this };
	//Cube->SetShader("Shaders.hlsl");
	//Objects.push_back(Cube);

	return S_OK;

}


void CRenderer::AddMesh(CStaticMesh* Mesh)
{
	if (Mesh)
	{
		Objects.push_back(Mesh);
	}
}


SShader CRenderer::SetShader(CStaticMesh* Mesh, std::string FilePath, bool UseDefaultPath)
{
	SFilePath File;
	if (UseDefaultPath)
	{
		File.FileName = FilePath;
		File.FilePath = DefaultFilePath;
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
	//BufferDesc.ByteWidth = sizeof(SModelVertex) * Mesh->GetVertexCount();
	BufferDesc.ByteWidth = sizeof(Mesh->GetVertices()[0]) * Mesh->GetVertexCount();
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HR = Setup->GetDevice()->CreateBuffer(&BufferDesc, NULL, &VertexBuffer);
	if (FAILED(HR)) return Shader;


	D3D11_BUFFER_DESC CBuffer;
	ZeroMemory(&CBuffer, sizeof(CBuffer));
	CBuffer.Usage = D3D11_USAGE_DEFAULT;
	CBuffer.ByteWidth = 80;
	CBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HR = Setup->GetDevice()->CreateBuffer(&CBuffer, NULL, &Shader.ConstantBuffer);



	D3D11_MAPPED_SUBRESOURCE MS;
	Setup->GetDeviceContext()->Map(VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &MS);
	memcpy(MS.pData, Mesh->GetVertices(), sizeof(Mesh->GetVertices()[0]) * Mesh->GetVertexCount());
	Setup->GetDeviceContext()->Unmap(VertexBuffer, NULL);


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
	};

	HR = Setup->GetDevice()->CreateInputLayout(IEDesc, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &Shader.InputLayout);
	if (FAILED(HR)) return Shader;

	Setup->GetDeviceContext()->IASetInputLayout(Shader.InputLayout);

	return Shader;
}


void CRenderer::DrawAll()
{
	// TODO:
	// TEMPORARY, MOVE TO INPUT CLASS
	if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}


	/// Actual Draw stuff.
	Setup->ClearView();


	SMatrix4 World;
	World.Identity();

	SMatrix4 View;
	SMatrix4 Projection;
	View.Indentity();

	SVector2i Size = Window->GetWindowSize();
	World.SetTranslate(0.0f, 0.0f, 5.0f);
	// This needs to change to get the window information.
	Projection = SMatrix4::PersepctiveFovLH(TO_RADIAN(45.0f), Size[X] / Size[Y], 1.0f, 100.0f);


	CBuffer CBValues;
	CBValues.RedFactor = 0.0f;
	CBValues.ViewMatrix = World * View * Projection;

	ID3D11Buffer* Buffer;
	for (uint i = 0; i < Objects.size(); ++i)
	{
		Buffer = Objects[i]->GetShader().ConstantBuffer;
		Setup->GetDeviceContext()->UpdateSubresource(Buffer, 0, 0, &CBValues, 0, 0);
		Setup->GetDeviceContext()->VSSetConstantBuffers(0, 1, &Buffer);
	
		//uint Stride = sizeof(SModelVertex);
		uint Stride = sizeof(SVertexBase);
		uint Offset = 0;
		Setup->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &Offset);
		Setup->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	
		Setup->GetDeviceContext()->Draw(Objects[i]->GetVertexCount(), 0);
	}

	Setup->GetSwapChain()->Present(0, 0);
}