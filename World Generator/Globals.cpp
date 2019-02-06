#include "Globals.h"

const int MaxUnitsOfLeastPrecision = 4;

std::string GetExePath()
{
	return fs::current_path().string();
}

bool DirectoryExists(std::string Directory)
{
	if (!fs::is_directory(Directory) || !fs::exists(Directory))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CreateDirectoryIfNull(std::string Directory)
{
	if (!DirectoryExists(Directory))
	{
		fs::create_directory(Directory);
	}
}