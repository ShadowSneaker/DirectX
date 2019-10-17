#define _CRT_SECURE_NO_WARNINGS

#include "StaticMesh.h"

#ifdef DXTRACE_MSG
#define RETURN_LOG_ERROR(String, Location) { {DXTRACE_MSG(String);} {DXTRACE_MSG(Location); return 0;} }
#endif


CLoadMesh::CLoadMesh(char* File, ID3D11Device* InDevice, ID3D11DeviceContext* InDeviceContext)
	:Device{ InDevice }, DeviceContext{ InDeviceContext }
{
	if (LoadFile(File) == 0)
	{
		FileName = "FILE NOT LOADED";
		return;
	}

	FileName = File;

	ParseFile();
	CreateVB();
	delete[] FBuffer;
}


CLoadMesh::~CLoadMesh()
{
	if (VertexBuffer) VertexBuffer->Release();
	delete[] Vertices;

	PositionList.clear();
	NormalList.clear();
	TexCoordList.clear();
}


void CLoadMesh::Draw()
{
	uint Stride = sizeof(SVertex);
	uint Offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &Offset);
	DeviceContext->Draw(VertexCount, 0);
}


int CLoadMesh::LoadFile(char* FileLocation)
{
	FILE* File;

	File = fopen(FileLocation, "r");
	if (File == NULL) 
	{ 
		RETURN_LOG_ERROR("Failed to open model file!", FileLocation);
	}

	fseek(File, 0, SEEK_END);
	FBufferSize = ftell(File);
	rewind(File);

	FBuffer = new char[FBufferSize + 1];
	if (FBuffer == NULL)
	{
		fclose(File);
		RETURN_LOG_ERROR("Failed to allocate memory for model file!", FileLocation);
	}

	ActualSize = fread(FBuffer, 1, FBufferSize, File);
	if (ActualSize == 0)
	{
		fclose(File);
		RETURN_LOG_ERROR("Failed to read model file!", FileLocation);
	}

	FBuffer[ActualSize] = '\n';
	fclose(File);
	return 1;
}


void CLoadMesh::ParseFile()
{
	TokenPtr = 0;

	int TokenStart;
	int TokenLength;

	SVector TempVec;
	SVector2 TempUV;

	bool Success;
	int Line{ 0 };

	do
	{
		++Line;

		if (!GetNextToken(TokenStart, TokenLength)) continue;

		if (strncmp(&FBuffer[TokenStart], "v ", 2) == 0)
		{
			Success = true;
			Success = Success && GetNextToken(TokenStart, TokenLength);
			TempVec[X] = (float)atof(&FBuffer[TokenStart]);
			Success = Success && GetNextToken(TokenStart, TokenLength);
			TempVec[Y] = (float)atof(&FBuffer[TokenStart]);
			Success = Success && GetNextToken(TokenStart, TokenLength);
			TempVec[Z] = (float)atof(&FBuffer[TokenStart]);

			if (!Success)
			{
				char S[100] = "Error: Badly formatted vertex line: ";
				_itoa(Line, &S[strlen(S)], 10);
				strcat(S, " : ");
				strcat(S, FileName.c_str());
				DXTRACE_MSG(S);
			}

			PositionList.push_back(TempVec);
		}
		else if (strncmp(&FBuffer[TokenStart], "vt", 2) == 0)
		{
			Success = true;
			Success = Success && GetNextToken(TokenStart, TokenLength);
			TempUV[X] = (float)atof(&FBuffer[TokenStart]);
			Success = Success && GetNextToken(TokenStart, TokenLength);
			TempUV[Y] = (float)atof(&FBuffer[TokenStart]);

			if (!Success)
			{
				char S[100] = "ERROR: Badly formatted normal, line : ";
				_itoa(Line, &S[strlen(S)], 10);
				strcat(S, " : ");
				strcat(S, FileName.c_str());
				DXTRACE_MSG(S);
			}

			TexCoordList.push_back(TempUV);
		}
		else if (strncmp(&FBuffer[TokenStart], "vn", 2) == 0)
		{
			Success = true;
			Success = Success && GetNextToken(TokenStart, TokenLength);
			TempVec[X] = (float)atof(&FBuffer[TokenStart]);
			Success = Success && GetNextToken(TokenStart, TokenLength);
			TempVec[Y] = (float)atof(&FBuffer[TokenStart]);
			Success = Success && GetNextToken(TokenStart, TokenLength);
			TempVec[Z] = (float)atof(&FBuffer[TokenStart]);

			if (!Success)
			{
				char S[100] = "ERROR: Badly formatted normal, line : ";
				_itoa(Line, &S[strlen(S)], 10);
				strcat(S, FileName.c_str());
				DXTRACE_MSG(S);
			}
			NormalList.push_back(TempVec);
		}
		else if (strncmp(&FBuffer[TokenStart], "f ", 2) == 0)
		{
			int TempPtr{ TokenStart + 2 };
			int ForwardSlashCount{ 0 };
			bool AdjacentSlash{ false };

			while (FBuffer[TempPtr] != '\n')
			{
				if (FBuffer[TempPtr] == '/')
				{
					++ForwardSlashCount;
					if (FBuffer[TempPtr - 1] == '/') AdjacentSlash = true;
				}
				++TempPtr;
			}

			Success = true;

			for (uint i = 0; i < 3; ++i)
			{
				Success = Success && GetNextToken(TokenStart, TokenLength);
				PIndices.push_back(atoi(&FBuffer[TokenStart]));

				if (ForwardSlashCount >= 3 && AdjacentSlash == false)
				{
					Success = Success && GetNextToken(TokenStart, TokenLength);
					TIndices.push_back(atoi(&FBuffer[TokenStart]));
				}

				if (ForwardSlashCount == 6 || AdjacentSlash == true)
				{
					Success = Success && GetNextToken(TokenStart, TokenLength);
					NIndices.push_back(atoi(&FBuffer[TokenStart]));
				}
			}

			if (!Success)
			{
				char S[100] = "ERROR: Badly formatted face, line : ";
				_itoa(Line, &S[strlen(S)], 10);
				strcat(S, " : ");
				strcat(S, FileName.c_str());
				DXTRACE_MSG(S);
			}
		}
	} while (GetNextLine() == true);
}


bool CLoadMesh::GetNextToken(int& TokenStart, int& TokenLength)
{
	TokenStart = TokenPtr;
	TokenLength = 1;
	int TokenEnd;

	while (FBuffer[TokenPtr] == ' ' || FBuffer[TokenPtr] == '\t' || FBuffer[TokenPtr] == '/') ++TokenPtr;

	if (FBuffer[TokenPtr] == '\n') { return false; }
	TokenEnd = TokenPtr + 1;

	while (FBuffer[TokenEnd] != ' ' && FBuffer[TokenEnd] != '\t' && FBuffer[TokenEnd] != '\n'  && FBuffer[TokenEnd] != '/') ++TokenEnd;

	TokenLength = TokenEnd - TokenPtr;
	TokenStart = TokenPtr;
	TokenPtr += TokenLength;

	return true;
}


bool CLoadMesh::GetNextLine()
{
	while (FBuffer[TokenPtr] != '\n' && TokenPtr < ActualSize) ++TokenPtr;

	++TokenPtr;

	return (TokenPtr < ActualSize);
}


bool CLoadMesh::CreateVB()
{
	VertexCount = PIndices.size();
	Vertices = new SVertex[VertexCount];

	for (uint i = 0; i < VertexCount; ++i)
	{
		int VIndex = PIndices[i] - 1;

		Vertices[i].Position = PositionList[VIndex];

		if (TIndices.size() > 0)
		{
			int TIndex = TIndices[i] - 1;
			Vertices[i].UV[X] = TexCoordList[TIndex][X];
			Vertices[i].UV[Y] = TexCoordList[TIndex][Y];
		}

		if (NIndices.size() > 0)
		{
			int NIndex = NIndices[i] - 1;
			Vertices[i].Normal = NormalList[NIndex];
		}
	}


	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth = sizeof(Vertices[0]) * VertexCount;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	HRESULT HR = Device->CreateBuffer(&BufferDesc, NULL, &VertexBuffer);

	if (FAILED(HR)) return false;

	D3D11_MAPPED_SUBRESOURCE MS;
	DeviceContext->Map(VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &MS);
	memcpy(MS.pData, Vertices, sizeof(Vertices[0]) * VertexCount);
	DeviceContext->Unmap(VertexBuffer, NULL);

	return true;
}








CStaticMesh::CStaticMesh(ID3D11Device* InDevice, ID3D11DeviceContext* InDeviceContext)
	:Device{ InDevice }, DeviceContext{ InDeviceContext }
{

}


HRESULT CStaticMesh::SetMesh(char* FileName)
{
	Object = new CLoadMesh(FileName, Device, DeviceContext);

	if (Object->FileName == "FILE NOT LOADED")
	{
		delete Object;
		return 0;
	}

	HRESULT HR;

	ID3DBlob* VS;
	ID3DBlob* PS;
	ID3DBlob* Error;

	HR = D3DX11CompileFromFile("model_shader.hlsl", 0, 0, "ModelVS", "vs_4_0", 0, 0, 0, &VS, &Error, 0);
	if (Error != 0)
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		Error->Release();
		if (FAILED(HR))
		{
			return HR;
		}
	}

	HR = D3DX11CompileFromFile("model_shader.hlsl", 0, 0, "ModelPS", "ps_4_0", 0, 0, 0, &PS, &Error, 0);
	if (Error != 0)
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		Error->Release();
		if (FAILED(HR))
		{
			return HR;
		}
	}

	HR = Device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &VShader);
	if (FAILED(HR)) return HR;

	HR = Device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &PShader);
	if (FAILED(HR)) return HR;

	DeviceContext->VSSetShader(VShader, 0, 0);
	DeviceContext->PSSetShader(PShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC IEDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};


	HR = Device->CreateInputLayout(IEDesc, ARRAYSIZE(IEDesc), VS->GetBufferPointer(), VS->GetBufferSize(), &InputLayout);
	if (FAILED(HR)) return HR;

	DeviceContext->IASetInputLayout(InputLayout);

	
	D3D11_BUFFER_DESC CBuffer;
	ZeroMemory(&CBuffer, sizeof(CBuffer));

	CBuffer.Usage = D3D11_USAGE_DEFAULT;
	CBuffer.ByteWidth = 64;
	CBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HR = Device->CreateBuffer(&CBuffer, NULL, &ConstantBuffer);
	if (FAILED(HR)) return HR;

	return WN_SUCCESS;
}


void CStaticMesh::Draw(SMatrix4* View, SMatrix4* Projection)
{
	SMatrix4 World;
	SMatrix4 Pos;
	SMatrix4 Rot;
	SMatrix4 Sca;
	Pos.SetToIdentity();
	Rot.SetToIdentity();
	Sca.SetToIdentity();

	Pos.SetTranslate(Location);
	Rot.SetRotate(Rotation);
	Sca.SetScale(SVector4{ Scale });

	World *= Sca * Rot * Pos;


	SModelBuffer MBuffer;
	MBuffer.WorldMatrix = World * *View * *Projection;
	
	DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);

	DeviceContext->VSSetShader(VShader, 0, 0);
	DeviceContext->PSSetShader(PShader, 0, 0);
}