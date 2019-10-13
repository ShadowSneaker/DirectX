#pragma once
#include <string>


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
};