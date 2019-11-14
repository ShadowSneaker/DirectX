#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "FileManager.h"
#include <fstream>


const String TFileManager::DefaultFilePath{ "Content/Assets/" };
const String TFileManager::MeshFilePath{ TFileManager::DefaultFilePath + "Meshes/" };
const String TFileManager::TextureFilePath{ TFileManager::DefaultFilePath + "Images/" };
const String TFileManager::ShaderFilePath{ TFileManager::DefaultFilePath + "Shaders/" };
const String TFileManager::FontFilePath{ TFileManager::DefaultFilePath + "Fonts/" };
const String TFileManager::LevelFilePath{ TFileManager::DefaultFilePath + "Levels/" };


SFileInfo TFileManager::ReadFile(String FilePath)
{
	FILE* File;
	File = fopen(FilePath.c_str(), "r");
	if (File == NULL)
	{
		LOG_ERROR("Failed to open model file!", FilePath.c_str());
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
		LOG_ERROR("Failed to allocate memory for model file!", FilePath.c_str());
		return SFileInfo{};
	}


	FileInfo.ActualSize = fread(FileInfo.Contents, 1, FileInfo.Size, File);
	if (FileInfo.ActualSize == 0)
	{
		fclose(File);
		LOG_ERROR("Failed to read file!", FilePath.c_str());
		return SFileInfo{};
	}

	FileInfo.Contents[FileInfo.ActualSize] = '\n';
	fclose(File);
	return FileInfo;
}


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


