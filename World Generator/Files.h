#ifndef FILES_H
#define FILES_H

#define RAPIDJSON_HAS_STDSTRING 1
#define _CRT_SECURE_NO_WARNINGS 1

#include "TGUI\TGUI.hpp"
#include "SFML\graphics.hpp"
#include "SFML\window.hpp"
#include "SFML\system.hpp"

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <ctime>
#include <queue>
#include <thread>
#include <cstdio>
#include <cstdlib>

#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

static std::string GetExePath()
{
	return fs::current_path().string();
}

static bool DirectoryExists(std::string Directory)
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

static void CreateDirectoryIfNull(std::string Directory)
{
	if (!DirectoryExists(Directory))
	{
		fs::create_directory(Directory);
	}
}

/*static std::string GetEXEPath(bool IncludeExeInPath)
{
	char result[MAX_PATH];
	std::string PathString = std::string(result, GetModuleFileName(NULL, result, MAX_PATH));

	if (IncludeExeInPath)
	{
		return PathString;
	}
	else
	{
		unsigned int ExeNameStart = PathString.length();
		for (unsigned int i = PathString.length(); i > 0; i--)
		{
			//std::cout << "PathString[" << i << "] = " << PathString[i] << std::endl;
			if (PathString.compare(i, 1, "\\") == 0 || PathString.compare(i, 1, "/") == 0)
			{
				//std::cout << "\\ or / found at " << i << ", PathString[i] = " << PathString[i] << std::endl;
				ExeNameStart = i;
				break;
			}
		}
		//std::cout << "EXENameStart = " << ExeNameStart << std::endl;
		PathString = PathString.substr(0, ExeNameStart + 1);
		//std::cout << "Final EXE Path: " << PathString << std::endl;
		return PathString;
	}
}*/

#endif // FILES_H
