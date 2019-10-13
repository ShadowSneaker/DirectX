#include "Font.h"


//CFont::CFont()
//{
//
//}


//CFont::CFont(std::string FileName, bool UseDefaultFilePath)
//{
//
//}


CFont::CFont(std::string FileName, ID3D11Device* InDevice, ID3D11DeviceContext* InDeviceContext)
	:Device{ InDevice }, DeviceContext{ InDeviceContext }
{
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth = sizeof(Vertices);
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	HRESULT HR = Device->CreateBuffer(&BufferDesc, NULL, &VertexBuffer);

	if (FAILED(HR)) exit(0);

	ID3DBlob* VS;
	ID3DBlob* PS;
	ID3DBlob* Error;

	HR = D3DX11CompileFromFile("text2D_shaders.hlsl", 0, 0, "TextVS", "vs_4_0", 0, 0, 0, &VS, &Error, 0);
	if (Error != 0)
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		Error->Release();
		if (FAILED(HR)) exit(0);
	}

	HR = D3DX11CompileFromFile("text2D_shaders.hlsl", 0, 0, "TextPS", "ps_4_0", 0, 0, 0, &PS, &Error, 0);
	if (Error != 0)
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		Error->Release();
		if (FAILED(HR)) exit(0);
	}

	HR = Device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &VShader);
	if (FAILED(HR)) exit(0);

	HR = Device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &PShader);
	if (FAILED(HR)) exit(0);

	D3D11_INPUT_ELEMENT_DESC IEDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	HR = Device->CreateInputLayout(IEDesc, ARRAYSIZE(IEDesc), VS->GetBufferPointer(), VS->GetBufferSize(), &InputLayout);
	if (FAILED(HR)) exit(0);

	HR = D3DX11CreateShaderResourceViewFromFile(Device, FileName.c_str(), NULL, NULL, &Texture, NULL);
	if (FAILED(HR)) exit(0);

	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HR = Device->CreateSamplerState(&SamplerDesc, &Sampler);

	D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
	DepthStencilDesc.DepthEnable = false;
	DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	DepthStencilDesc.StencilEnable = true;
	DepthStencilDesc.StencilReadMask = 0xFF;
	DepthStencilDesc.StencilWriteMask = 0xFF;
	DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	DepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	DepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HR = Device->CreateDepthStencilState(&DepthStencilDesc, &DepthDisabledStencilState);
	if (FAILED(HR)) exit(0);

	DepthStencilDesc.DepthEnable = true;
	HR = Device->CreateDepthStencilState(&DepthStencilDesc, &DepthEnabledStencilState);
	if (FAILED(HR)) exit(0);

	
}


CFont::~CFont()
{
	if (DepthDisabledStencilState) DepthDisabledStencilState->Release();
	if (DepthEnabledStencilState) DepthEnabledStencilState->Release();
	if (Texture) Texture->Release();
	if (Sampler) Sampler->Release();
	if (VertexBuffer) VertexBuffer->Release();
	if (VShader) VShader->Release();
	if (PShader) PShader->Release();
	if (InputLayout) InputLayout->Release();
}


void CFont::RenderText()
{
	int CurrentCharacter{ 0 };

	float TempX{ Location[X] };

	// Loop through each character.
	for (uint i = 0; i < Text.size(); ++i)
	{
		Vertices[CurrentCharacter * 6].Position[X] = TempX;
		Vertices[CurrentCharacter * 6].Position[Y] = Location[Y];
		Vertices[CurrentCharacter * 6 + 1].Position[X] = TempX + Size; //+ (Location[X]);
		Vertices[CurrentCharacter * 6 + 1].Position[Y] = Location[Y];		//
		Vertices[CurrentCharacter * 6 + 2].Position[X] = TempX + Size; //+ (Location[X]);
		Vertices[CurrentCharacter * 6 + 2].Position[Y] = Location[Y] - Size; //+ (Location[X]);
		Vertices[CurrentCharacter * 6 + 3].Position[X] = TempX;		//
		Vertices[CurrentCharacter * 6 + 3].Position[Y] = Location[Y];		//
		Vertices[CurrentCharacter * 6 + 4].Position[X] = TempX + Size; //+ (Location[X]);
		Vertices[CurrentCharacter * 6 + 4].Position[Y] = Location[Y] - Size; //+ (Location[X]);
		Vertices[CurrentCharacter * 6 + 5].Position[X] = TempX;		//
		Vertices[CurrentCharacter * 6 + 5].Position[Y] = Location[Y] - Size; //+ (Location[X]);

		Vertices[CurrentCharacter * 6].Position[Z] = 1.0f;
		Vertices[CurrentCharacter * 6 + 1].Position[Z] = 1.0f;
		Vertices[CurrentCharacter * 6 + 2].Position[Z] = 1.0f;
		Vertices[CurrentCharacter * 6 + 3].Position[Z] = 1.0f;
		Vertices[CurrentCharacter * 6 + 4].Position[Z] = 1.0f;
		Vertices[CurrentCharacter * 6 + 5].Position[Z] = 1.0f;

		const int NUMLINES = 4;

		char C = Text[i];

		float TexX;
		float TexY;

		if (C >= 'a' && C <= 'z')
		{
			TexY = 0.0f;
			TexX = (C - 'a') * (1.0f / 26.0f);
		}
		else if (C >= 'A' && C <= 'Z')
		{
			TexY = 1.0f / NUMLINES;
			TexX = (C - 'A') * (1.0f / 26.0f);
		}
		else if (C >= '0' && C <= '9')
		{
			TexY = 2.0f / NUMLINES;
			TexX = (C - '0') * (1.0f / 26.0f);
		}
		else
		{
			TexX = 0.0f;
			TexY = 3.0f / NUMLINES;
		}


		Vertices[CurrentCharacter * 6].UV[X] = TexX;
		Vertices[CurrentCharacter * 6].UV[Y] = TexY;
		Vertices[CurrentCharacter * 6 + 1].UV[X] = TexX + (1.0f / 26.0f);
		Vertices[CurrentCharacter * 6 + 1].UV[Y] = TexY;
		Vertices[CurrentCharacter * 6 + 2].UV[X] = TexX + (1.0f / 26.0f);
		Vertices[CurrentCharacter * 6 + 2].UV[Y] = TexY + (1.0f / NUMLINES);
		Vertices[CurrentCharacter * 6 + 3].UV[X] = TexX;
		Vertices[CurrentCharacter * 6 + 3].UV[Y] = TexY;
		Vertices[CurrentCharacter * 6 + 4].UV[X] = TexX + (1.0f / 26.0f);
		Vertices[CurrentCharacter * 6 + 4].UV[Y] = TexY + (1.0f / NUMLINES);
		Vertices[CurrentCharacter * 6 + 5].UV[X] = TexX;
		Vertices[CurrentCharacter * 6 + 5].UV[Y] = TexY + (1.0f / NUMLINES);

		++CurrentCharacter;
		TempX += Size;
	}

	D3D11_MAPPED_SUBRESOURCE MS;
	DeviceContext->Map(VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &MS);
	memcpy(MS.pData, Vertices, sizeof(Vertices[0]) * CurrentCharacter * 6);
	DeviceContext->Unmap(VertexBuffer, NULL);

	DeviceContext->PSSetSamplers(0, 1, &Sampler);
	DeviceContext->PSSetShaderResources(0, 1, &Texture);
	DeviceContext->VSSetShader(VShader, 0, 0);			// This line removes the cube.
	DeviceContext->PSSetShader(PShader, 0, 0);			// This line removes the texture and colour on the cube.
	DeviceContext->IASetInputLayout(InputLayout);		// This line removes the colour on the cube.
	
	uint Stride = sizeof(STempVertex);
	uint Offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &Offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	DeviceContext->OMSetDepthStencilState(DepthDisabledStencilState, 1);
	
	DeviceContext->Draw(CurrentCharacter * 6, 0);
	
	DeviceContext->OMSetDepthStencilState(DepthEnabledStencilState, 1);
}