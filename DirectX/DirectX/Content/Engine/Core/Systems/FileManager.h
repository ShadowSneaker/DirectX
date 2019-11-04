#pragma once
#include "../../Math/MathValues.h"

#include <string>
#include <vector>

#include <stdio.h>
#include <D3D11.h>
#include <DXGI.h>
#include <D3DX11.h>
#include <DxErr.h>
//#include <Windows.h>


#ifdef DXTRACE_MSG
#define LOG_ERROR(String, Location) { {DXTRACE_MSG(String);} {DXTRACE_MSG(Location);} }
#endif


typedef std::string String;
typedef std::vector<String> SStringBlock;


struct SFilePath
{
	/// Properties

	// The name of the file.
	String FileName;

	// The path to the file.
	// Note: this does not contain the actual file name.
	String FilePath;


	/// Getters

	// Gets the full file path of this file, including the path and the name.
	inline String GetFilePath() const { return FilePath + FileName; };


	// Returns a correctly formatted SFilePath object.
	// Note: This will only work if the inputted file string is the complete path.
	// @param File - The file location.
	// @return - The correctly formatted file path.
	static SFilePath GetFileName(String File)
	{
		SFilePath FilePath;
		for (uint i = File.length() - 1; i > 0; --i)
		{
			if (File[i] == '/')
			{
				FilePath.FileName = File.substr(i + 1);
				FilePath.FilePath = File.substr(0, i + 1);
			}
		}
		return FilePath;
	}
};


// TODO write description.
struct SFileInfo
{
	// The amount of lines the file has.
	int32 Size;

	// The contents of the file.
	char* Contents;

	uint ActualSize;
};


// TODO write description.
class TFileManager
{
public:
	/// Static Constants

	// Holds all the common asset locations.

	// The default location of where content files are located.
	static const String DefaultFilePath;

	// The default location for meshes.
	static const String MeshFilePath;

	// The default location for textures.
	static const String TextureFilePath;

	// The default location for shaders.
	static const String ShaderFilePath;

	// The default location for fonts.
	static const String FontFilePath;



	/// Static Functions


	// Reads an inputted file and returns all of the files contents.
	// @param FilePath - The file location of the file to read.
	// @return - Returns a copy of every line in the file.
	static SFileInfo ReadFile(char* FilePath)
	{
		FILE* File;
		fopen_s(&File, FilePath, "r");
		if (File == NULL)
		{
			LOG_ERROR("Failed to open model file!", FilePath);
			return SFileInfo{};
		}
		
		SFileInfo FileInfo;

		fseek(File, 0, SEEK_END);
		FileInfo.Size = ftell(File);
		rewind(File);

		FileInfo.Contents = new char[FileInfo.Size + 1];
		if (FileInfo.Contents == NULL)
		{
			fclose(File);
			LOG_ERROR("Failed to allocate memory for model file!", FilePath);
			return SFileInfo{};
		}


		FileInfo.ActualSize = fread(FileInfo.Contents, 1, FileInfo.Size, File);
		if (FileInfo.ActualSize == 0)
		{
			fclose(File);
			LOG_ERROR("Failed to read file!", FilePath);
			return SFileInfo{};
		}
		
		FileInfo.Contents[FileInfo.ActualSize] = '\n';
		fclose(File);
		return FileInfo;
	}
};


