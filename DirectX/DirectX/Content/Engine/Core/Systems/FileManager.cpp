#include "FileManager.h"
#include <fstream>


const String TFileManager::DefaultFilePath{ "Content/Assets/" };
const String TFileManager::MeshFilePath{ TFileManager::DefaultFilePath + "Meshes/" };
const String TFileManager::TextureFilePath{ TFileManager::DefaultFilePath + "Images/" };
const String TFileManager::ShaderFilePath{ TFileManager::DefaultFilePath + "Shaders/" };
const String TFileManager::FontFilePath{ TFileManager::DefaultFilePath + "Fonts/" };
const String TFileManager::LevelFilePath{ TFileManager::DefaultFilePath + "Levels/" };


SStringBlock TFileManager::ReadFileAlt(String File)
{
	SStringBlock Contents;
	std::ifstream OpenFile;
	OpenFile.open(File.c_str());

	if (OpenFile.bad())
	{
		return Contents;
	}

	while (!OpenFile.eof())
	{
		String Line;
		std::getline(OpenFile, Line);
		Contents.push_back(Line);
	}

	OpenFile.close();
	return Contents;
}


SStringBlock TFileManager::LineToWord(String Data)
{
	std::istringstream ISS{ Data };
	String LastWord{ "" };
	String Value;

	SStringBlock Info;

	while (ISS)
	{
		String Word;
		ISS >> Word;
		Info.push_back(Word);
	}
	return Info;
}


template <uint Size, typename Type> 
Vector<Size, Type> TFileManager::ReadVector(String DataLine)
{
	std::istringstream ISS{ DataLine };
	String LastWord{ "" };

	Vector<Size, Type> Result;

	while (ISS)
	{
		String Word;
		ISS >> Word;

		if (LastWord == "=")
		{
			for (uint i = 0; i < Size; ++i)
			{
				Result[i] = (Type)atof(Word.c_str());
				ISS >> Word;
			}
			return Result;
		}
		LastWord = Word;
	}
}


