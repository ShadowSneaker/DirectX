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
	uint Stride = sizeof(SMeshVertex);
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
	Vertices = new SMeshVertex[VertexCount];

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
// draw object
/*void ObjFileModel::Draw(void)
{
	UINT stride = sizeof(MODEL_POS_TEX_NORM_VERTEX);
	UINT offset = 0;
	pImmediateContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	pImmediateContext->Draw(numverts, 0);
}


// load object from obj file in constructor
ObjFileModel::ObjFileModel(char* fname, ID3D11Device* device, ID3D11DeviceContext* context)
{
	pD3DDevice = device;
	pImmediateContext = context;

	if (loadfile(fname) == 0)
	{
		// file not loaded, check debug output;
		filename = "FILE NOT LOADED";
		return;
	}

	filename = fname;

	parsefile();

	createVB();

	delete[] fbuffer; // delete file buffer created in loadfile()
}


// load wavefront object file. adds terminating \n so last line of file can be correctly parsed as a 'line' later
// basic loader - only deals with vertices v, texcoords vt, normals vn 
//              - only copes with triangular meshes (no quads)
//              - doesn't deal with textures or materials
int ObjFileModel::loadfile(char* fname)
{
	FILE* pFile;

	pFile = fopen(fname, "r"); // if changed to bin format will read carriage return \r (0d) as well as \n (0a) into fbuffer, may need to add \r checks(but seemed to work with basic test)
	if (pFile == NULL) { DXTRACE_MSG("Failed to open model file"); DXTRACE_MSG(fname); return 0; }

	// get file size
	fseek(pFile, 0, SEEK_END);
	fbuffersize = ftell(pFile);
	rewind(pFile);

	// allocate memory for entire file size
	fbuffer = new char[fbuffersize + 1]; // 1 added to cope with adding a \n later in case file doesn't end with \n 
	if (fbuffer == NULL) { fclose(pFile); DXTRACE_MSG("Failed allocate memory for model file"); DXTRACE_MSG(fname); return 0; }

	// copy file into memory
	actualsize = fread(fbuffer, 1, fbuffersize, pFile); // actualsize may be less than fbuffersize in text mode as \r are stripped
	if (actualsize == 0) { fclose(pFile); DXTRACE_MSG("Failed to read model file"); DXTRACE_MSG(fname); return 0; }

	// add a newline at end in case file does not, so can deal with whole buffer as a set of lines of text
	fbuffer[actualsize] = '\n'; fclose(pFile);

	return 1;
}


// uses concept of getting parsable tokens seperated by whitespace and '/'
// one line of file is parsed at a time, lines seperated by '\n'
void ObjFileModel::parsefile()
{
	tokenptr = 0; // token pointer points to first element of buffer

	int tokenstart, tokenlength;

	xyz tempxyz;
	xy tempxy;

	bool success;
	int line = 0;

	do
	{
		line++; // keep track of current line number for error reporting

		if (!getnexttoken(tokenstart, tokenlength)) continue; // get first token on line, go to next line if first token is \n

		// ADD FURTHER KEYWORDS HERE TO EXTEND CAPABILITIES
		if (strncmp(&fbuffer[tokenstart], "v ", 2) == 0) // VERTEX POSITION - note the space in the string is needed (see vt, etc)
		{
			success = true; // used to see if correct number of tokens left on line for this type of attribute
			success = success && getnexttoken(tokenstart, tokenlength);
			tempxyz.x = (float)atof(&fbuffer[tokenstart]);
			success = success && getnexttoken(tokenstart, tokenlength);
			tempxyz.y = (float)atof(&fbuffer[tokenstart]);
			success = success && getnexttoken(tokenstart, tokenlength);
			tempxyz.z = (float)atof(&fbuffer[tokenstart]);

			// if not correct number of tokens, display error in debug output
			if (!success) { char s[100] = "ERROR: Badly formatted vertex, line : "; _itoa(line, &s[strlen(s)], 10); strcat(s, " : "); strcat(s, filename.c_str());  DXTRACE_MSG(s); }

			position_list.push_back(tempxyz); // add a new element to the list

		}
		else if (strncmp(&fbuffer[tokenstart], "vt", 2) == 0) // TEXTURE COORDINATES
		{
			success = true;
			success = success && getnexttoken(tokenstart, tokenlength);
			tempxy.x = (float)atof(&fbuffer[tokenstart]);
			success = success && getnexttoken(tokenstart, tokenlength);
			tempxy.y = (float)atof(&fbuffer[tokenstart]);

			if (!success) { char s[100] = "ERROR: Badly formatted texture coordinate, line : "; _itoa(line, &s[strlen(s)], 10); strcat(s, " : "); strcat(s, filename.c_str());  DXTRACE_MSG(s); }

			texcoord_list.push_back(tempxy);
		}
		else if (strncmp(&fbuffer[tokenstart], "vn", 2) == 0)  // NORMALS
		{
			success = true;
			success = success && getnexttoken(tokenstart, tokenlength);
			tempxyz.x = (float)atof(&fbuffer[tokenstart]);
			success = success && getnexttoken(tokenstart, tokenlength);
			tempxyz.y = (float)atof(&fbuffer[tokenstart]);
			success = success && getnexttoken(tokenstart, tokenlength);
			tempxyz.z = (float)atof(&fbuffer[tokenstart]);

			if (!success) { char s[100] = "ERROR: Badly formatted normal, line : "; _itoa(line, &s[strlen(s)], 10); strcat(s, " : "); strcat(s, filename.c_str());  DXTRACE_MSG(s); }

			normal_list.push_back(tempxyz);
		}
		else if (strncmp(&fbuffer[tokenstart], "f ", 2) == 0)  // FACE - only deals with triangles so far
		{
			int tempptr = tokenstart + 2; // skip "f "
			int forwardslashcount = 0;
			bool adjacentslash = false;

			// this works out how many elements are specified for a face, e.g.
			// f 1 2 3				-> 0 forward slashes = just position
			// f 1/1 2/2 3/3		-> 3 slashes = position and texcoords
			// f 1/1/1 2/2/2 3/3/3	-> 6 slashes = position, texcoords, normals
			// f 1//1 2//2 3//3		-> 6 slashes with adjacent = position, normals
			while (fbuffer[tempptr] != '\n')
			{
				if (fbuffer[tempptr] == '/')
				{
					forwardslashcount++;
					if (fbuffer[tempptr - 1] == '/') adjacentslash = true;
				}
				tempptr++;
			}

			success = true;

			// Get 3 sets of indices per face
			for (int i = 0; i < 3; i++)
			{
				// get vertex index
				success = success && getnexttoken(tokenstart, tokenlength);
				pindices.push_back(atoi(&fbuffer[tokenstart]));

				if (forwardslashcount >= 3 && adjacentslash == false) // get texcoord index if required 
				{
					success = success && getnexttoken(tokenstart, tokenlength);
					tindices.push_back(atoi(&fbuffer[tokenstart]));
				}

				if (forwardslashcount == 6 || adjacentslash == true) // get normal index if required 
				{
					success = success && getnexttoken(tokenstart, tokenlength);
					nindices.push_back(atoi(&fbuffer[tokenstart]));
				}
			}

			if (!success) { char s[100] = "ERROR: Badly formatted face, line : "; _itoa(line, &s[strlen(s)], 10); strcat(s, " : "); strcat(s, filename.c_str());  DXTRACE_MSG(s); }
		}
	} while (getnextline() == true);
}


// get next token. if \n is next token do not proceed, use getnextline() to resume
bool ObjFileModel::getnexttoken(int& tokenstart, int& tokenlength)
{
	tokenstart = tokenptr;
	tokenlength = 1;
	int tokenend;

	while (fbuffer[tokenptr] == ' ' || fbuffer[tokenptr] == '\t' || fbuffer[tokenptr] == '/') tokenptr++; //skip whitespace and '/'

	if (fbuffer[tokenptr] == '\n') { return false; } // keeps tokenptr pointing to \n as a token to indicate end of line
													// doesn't point to next token, dealt with in getnextline()
	tokenend = tokenptr + 1;

	while (fbuffer[tokenend] != ' ' && fbuffer[tokenend] != '\t' && fbuffer[tokenend] != '\n' && fbuffer[tokenend] != '/') tokenend++; // find length of token by finding next whitespace or '\n' or '/'

	tokenlength = tokenend - tokenptr;
	tokenstart = tokenptr;
	tokenptr += tokenlength; //ready for next token

	return true;
}


// gets next line of buffer by skipping to next element after end of current line, returns false when end of buffer exceeded
bool ObjFileModel::getnextline()
{
	// relies on getnexttoken()leaving tokenptr pointing to \n if encountered

	while (fbuffer[tokenptr] != '\n' && tokenptr < actualsize) tokenptr++; // skip to end of line

	tokenptr++; // point to start of next line

	if (tokenptr >= actualsize) return false;
	else return true;
}


// create Vertex buffer from parsed file data
bool ObjFileModel::createVB()
{
	// create vertex array to pass to vertex buffer from parsed data
	numverts = pindices.size();

	vertices = new MODEL_POS_TEX_NORM_VERTEX[numverts]; // create big enough vertex array

	for (unsigned int i = 0; i < numverts; i++)
	{
		int vindex = pindices[i] - 1; // use -1 for indices as .obj files indices begin at 1

		// set position data
		vertices[i].Pos.x = position_list[vindex].x;
		vertices[i].Pos.y = position_list[vindex].y;
		vertices[i].Pos.z = position_list[vindex].z;

		if (tindices.size() > 0)
		{
			// if there are any, set texture coord data
			int tindex = tindices[i] - 1;
			vertices[i].TexCoord.x = texcoord_list[tindex].x;
			vertices[i].TexCoord.y = texcoord_list[tindex].y;
		}

		if (nindices.size() > 0)
		{
			// if there are any, set normal data
			int nindex = nindices[i] - 1;
			vertices[i].Normal.x = normal_list[nindex].x;
			vertices[i].Normal.y = normal_list[nindex].y;
			vertices[i].Normal.z = normal_list[nindex].z;
		}
	}

	// Set up and create vertex buffer
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;										// Used by CPU and GPU
	bufferDesc.ByteWidth = sizeof(vertices[0]) * numverts;						// Total size of buffer
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;							// Use as a vertex buffer
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;							// Allow CPU access
	HRESULT hr = pD3DDevice->CreateBuffer(&bufferDesc, NULL, &pVertexBuffer);	// Create the buffer

	if (FAILED(hr))
	{
		return false;
	}

	// Copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	pImmediateContext->Map(pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);	// Lock the buffer to allow writing
	memcpy(ms.pData, vertices, sizeof(vertices[0]) * numverts);							// Copy the data
	pImmediateContext->Unmap(pVertexBuffer, NULL);										// Unlock the buffer

	return true;
}


ObjFileModel::~ObjFileModel()
{
	// clean up memory used by object
	if (pVertexBuffer) pVertexBuffer->Release();

	delete[] vertices;

	position_list.clear();
	normal_list.clear();
	texcoord_list.clear();
}*/








CStaticMesh::CStaticMesh(ID3D11Device* InDevice, ID3D11DeviceContext* InDeviceContext)
	:Device{ InDevice }, DeviceContext{ InDeviceContext }
{

}


CStaticMesh::~CStaticMesh()
{
	delete Object;
	if (PShader) PShader->Release();
	if (VShader) VShader->Release();
	if (InputLayout) InputLayout->Release();
}


HRESULT CStaticMesh::SetMesh(char* FileName)
{
	Object = new CLoadMesh(FileName, Device, DeviceContext);
	//Object = new ObjFileModel{ FileName, Device, DeviceContext };

	if (Object->FileName == "FILE NOT LOADED")
	//if (Object->filename == "FILE NOT LOADED")
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
	//DirectX::XMMATRIX W;
	//DirectX::XMMATRIX P;
	//DirectX::XMMATRIX R;
	//DirectX::XMMATRIX S;
	//
	//W = DirectX::XMMatrixTranslation(Location[X], Location[Y], Location[Z]);
	//W *= DirectX::XMMatrixRotationRollPitchYaw(Rotation[X], Rotation[Y], Rotation[Z]);
	//W *= DirectX::XMMatrixScaling(Scale, Scale, Scale);



	SMatrix4 World;
	SMatrix4 Pos;
	SMatrix4 Rot;
	SMatrix4 Sca;
	World.SetToIdentity();
	Rot.SetToIdentity();


	//Pos = Pos.Translate(Location);
	Pos.SetTranslate(Location);
	Rot.SetRotate(Rotation);
	Sca.SetScale(SVector{ Scale });

	World = Sca * Rot * Pos;


	SModelBuffer MBuffer;
	MBuffer.WorldMatrix = World * *View * *Projection;
	
	DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);
	DeviceContext->UpdateSubresource(ConstantBuffer, 0, 0, &MBuffer, 0, 0);


	DeviceContext->VSSetShader(VShader, 0, 0);
	DeviceContext->PSSetShader(PShader, 0, 0);
	DeviceContext->IASetInputLayout(InputLayout);

	Object->Draw();
}