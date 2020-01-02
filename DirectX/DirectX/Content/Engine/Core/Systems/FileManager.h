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


// A tyepdef for a string.
typedef std::string String;

// A typedef of a vector of strings.
typedef std::vector<String> SStringBlock;



// Helper structure to store the file path and file name of a file.
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



// Stores the contents of a file and other gerneral information about the file.
struct SFileInfo
{
	// The amount of lines the file has.
	long Size{ 0 };

	// The contents of the file.
	char* Contents{ nullptr };

	// The amount of lines in the file.
	uint ActualSize{ 0 };



	/// Functions
	
	// Cleans up any references this object has.
	void Clear()
	{
		delete[] Contents;
	}
};


// Static functions to help reading and writing to files.
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

	// Returns true if the file exists.
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

	// Reads the contents of the file and stores it in an array of strings.
	// @param FilePath - The file location of the file to read.
	// @return - Returns every line of the file in a array of strings.
	static SStringBlock ReadFileAlt(String FilePath);

	// Reads a string and converts every word in the string into a seperate index in an array.
	// @param Data - The string to read.
	// @return - The converted string.
	static SStringBlock LineToWord(String Data);

	// Reads a string and converts every number into a vector.
	// @template Size - The amount of dimensions the vector should have.
	// @template Type - The datatype the vector should have.
	// @param DataLine - The string to read.
	// @return - A vector with the values in the file.
	template <uint Size, typename Type = float>
	static Vector<Size, Type> ReadVector(String DataLine);

	// Converts a string to a number.
	// @template Type - The datatype the string should be converted to.
	// @param Data - The string of the value to convert.
	// @return - The converted value.
	template <typename Type>
	static Type GetValue(String Data)
	{
		std::istringstream ISS{ Data };
		Type Value;
		ISS >> Value;
		return Value;
	}
};