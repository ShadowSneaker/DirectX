#pragma once
#include <string>
#include "../../Math/MathValues.h"


struct SFilePath
{
	/// Properties

	// The name of the file.
	std::string FileName;

	// The path to the file.
	// Note: this does not contain the actual file name.
	std::string FilePath;


	/// Getters

	// Gets the full file path of this file, including the path and the name.
	inline std::string GetFilePath() const { return FilePath + FileName; };


	// Returns a correctly formatted SFilePath object.
	// Note: This will only work if the inputted file string is the complete path.
	// @param File - The file location.
	// @return - The correctly formatted file path.
	static SFilePath GetFileName(std::string File)
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