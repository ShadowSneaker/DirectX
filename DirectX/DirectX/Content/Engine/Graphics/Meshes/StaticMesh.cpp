#define _CRT_SECURE_NO_WARNINGS

#include "StaticMesh.h"
#include "../Renderer.h"



CStaticMesh::CStaticMesh()
{
	
}


CStaticMesh::~CStaticMesh()
{
	Shader.Clear();
	delete[] Vertices;

	PositionList.clear();
	NormalList.clear();
	TexCoordList.clear();
}


void CStaticMesh::SetupVertices(SFileInfo FileInfo)
{
	if (VertexCount > 0) delete[] Vertices;

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

		if (!GetNextToken(FileInfo, TokenStart, TokenLength)) continue;

		if (strncmp(&FileInfo.Contents[TokenStart], "v ", 2) == 0)
		{
			Success = true;
			Success = Success && GetNextToken(FileInfo, TokenStart, TokenLength);
			TempVec[X] = (float)atof(&FileInfo.Contents[TokenStart]);
			Success = Success && GetNextToken(FileInfo, TokenStart, TokenLength);
			TempVec[Y] = (float)atof(&FileInfo.Contents[TokenStart]);
			Success = Success && GetNextToken(FileInfo, TokenStart, TokenLength);
			TempVec[Z] = (float)atof(&FileInfo.Contents[TokenStart]);

			if (!Success)
			{
				char S[100] = "Error: Badly formatted vertex line: ";
				_itoa(Line, &S[strlen(S)], 10);
				strcat(S, " : ");
				strcat(S, FileName.GetFilePath().c_str());
				DXTRACE_MSG(S);
			}

			PositionList.push_back(TempVec);
		}
		else if (strncmp(&FileInfo.Contents[TokenStart], "vt", 2) == 0)
		{
			Success = true;
			Success = Success && GetNextToken(FileInfo, TokenStart, TokenLength);
			TempUV[X] = (float)atof(&FileInfo.Contents[TokenStart]);
			Success = Success && GetNextToken(FileInfo, TokenStart, TokenLength);
			TempUV[Y] = (float)atof(&FileInfo.Contents[TokenStart]);

			if (!Success)
			{
				char S[100] = "ERROR: Badly formatted normal, line : ";
				_itoa(Line, &S[strlen(S)], 10);
				strcat(S, " : ");
				strcat(S, FileName.GetFilePath().c_str());
				DXTRACE_MSG(S);
			}

			TexCoordList.push_back(TempUV);
		}
		else if (strncmp(&FileInfo.Contents[TokenStart], "vn", 2) == 0)
		{
			Success = true;
			Success = Success && GetNextToken(FileInfo, TokenStart, TokenLength);
			TempVec[X] = (float)atof(&FileInfo.Contents[TokenStart]);
			Success = Success && GetNextToken(FileInfo, TokenStart, TokenLength);
			TempVec[Y] = (float)atof(&FileInfo.Contents[TokenStart]);
			Success = Success && GetNextToken(FileInfo, TokenStart, TokenLength);
			TempVec[Z] = (float)atof(&FileInfo.Contents[TokenStart]);

			if (!Success)
			{
				char S[100] = "ERROR: Badly formatted normal, line : ";
				_itoa(Line, &S[strlen(S)], 10);
				strcat(S, FileName.GetFilePath().c_str());
				DXTRACE_MSG(S);
			}
			NormalList.push_back(TempVec);
		}
		else if (strncmp(&FileInfo.Contents[TokenStart], "f ", 2) == 0)
		{
			int TempPtr{ TokenStart + 2 };
			int ForwardSlashCount{ 0 };
			bool AdjacentSlash{ false };

			while (FileInfo.Contents[TempPtr] != '\n')
			{
				if (FileInfo.Contents[TempPtr] == '/')
				{
					++ForwardSlashCount;
					if (FileInfo.Contents[TempPtr - 1] == '/') AdjacentSlash = true;
				}
				++TempPtr;
			}

			Success = true;

			for (uint i = 0; i < 3; ++i)
			{
				Success = Success && GetNextToken(FileInfo, TokenStart, TokenLength);
				PIndices.push_back(atoi(&FileInfo.Contents[TokenStart]));

				if (ForwardSlashCount >= 3 && AdjacentSlash == false)
				{
					Success = Success && GetNextToken(FileInfo, TokenStart, TokenLength);
					TIndices.push_back(atoi(&FileInfo.Contents[TokenStart]));
				}

				if (ForwardSlashCount == 6 || AdjacentSlash == true)
				{
					Success = Success && GetNextToken(FileInfo, TokenStart, TokenLength);
					NIndices.push_back(atoi(&FileInfo.Contents[TokenStart]));
				}
			}

			if (!Success)
			{
				char S[100] = "ERROR: Badly formatted face, line : ";
				_itoa(Line, &S[strlen(S)], 10);
				strcat(S, " : ");
				strcat(S, FileName.GetFilePath().c_str());
				DXTRACE_MSG(S);
			}
		}
	} while (GetNextLine(FileInfo) == true);






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
}


bool CStaticMesh::GetNextToken(SFileInfo File, int& Start, int& Length)
{
	Start = TokenPtr;
	Length = 1;
	int TokenEnd;

	while (File.Contents[TokenPtr] == ' ' || File.Contents[TokenPtr] == '\t' || File.Contents[TokenPtr] == '/') ++TokenPtr;

	if (File.Contents[TokenPtr] == '\n') { return false; }
	TokenEnd = TokenPtr + 1;

	while (File.Contents[TokenEnd] != ' ' && File.Contents[TokenEnd] != '\t' && File.Contents[TokenEnd] != '\n' && File.Contents[TokenEnd] != '/') ++TokenEnd;

	Length = TokenEnd - TokenPtr;
	Start = TokenPtr;
	TokenPtr += Length;

	return true;
}


bool CStaticMesh::GetNextLine(SFileInfo File)
{
	while (File.Contents[TokenPtr] != '\n' && TokenPtr < File.ActualSize) ++TokenPtr;

	++TokenPtr;

	return (TokenPtr < File.ActualSize);
}


void CStaticMesh::SetMesh(String FilePath, bool UseDefaultPath)
{
	SFilePath File;
	if (UseDefaultPath)
	{
		File.FileName = FilePath;
		File.FilePath = TFileManager::MeshFilePath;
	}
	else
	{
		File = SFilePath::GetFileName(FilePath);
	}


	SFileInfo Info{ TFileManager::ReadFile(File.GetFilePath()) };
	if (Info.ActualSize == 0)
	{
		File.FileName = "FILE NOT LOADED";
		File.FilePath.clear();
		return;
	}
	FilePath = File;


	SetupVertices(Info);
	Info.Clear();
}


void CStaticMesh::SetColour(float Red, float Green, float Blue, float Alpha)
{
	SetColour(SColour{ Red, Green, Blue, Alpha });
}


void CStaticMesh::SetColour(SColour Colour)
{
	for (uint i = 0; i < VertexCount; ++i)
	{
		Vertices[i].Colour = Colour;
	}
}


SShader CStaticMesh::GetShader() const
{
	return Shader;
}