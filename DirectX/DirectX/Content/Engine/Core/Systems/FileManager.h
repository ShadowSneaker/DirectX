#pragma once



#include "../../Math/MathValues.h"
#include "../../Math/DataTypes/Vector.h"

#include <string>
#include <vector>
#include <sstream>

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


	/// Operators

	// Used to get this object to return the file name without requring to access the file name directly.
	inline operator String() const { return FileName; }


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
	long Size{ 0 };

	// The contents of the file.
	char* Contents{ nullptr };

	uint ActualSize{ 0 };


	/// Functions
	
	// Cleans up any references this object has.
	void Clear()
	{
		delete[] Contents;
	}
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

	// The default location for levels.
	static const String LevelFilePath;



	/// Static Functions


	// Reads an inputted file and returns all of the files contents.
	// @param FilePath - The file location of the file to read.
	// @return - Returns a copy of every line in the file.
	static SFileInfo ReadFile(String FilePath);


	static bool DoesFileExist(String FilePath)
	{
		FILE* File;
		fopen_s(&File, FilePath.c_str(), "r");

		if (File != NULL)
		{
			fclose(File);
			return true;
		}
		return false;
	}


	static SStringBlock ReadFileAlt(String FilePath);

	static SStringBlock LineToWord(String Data);

	template <uint Size, typename Type>
	static Vector<Size, Type> ReadVector(String DataLine);

	template <typename Type>
	static Type GetValue(String Data)
	{
		std::istringstream ISS{ Data };
		Type Value;
		ISS >> Value;
		return Value;
		//return (Type)atoi(Data.c_str());
		
	}
};


