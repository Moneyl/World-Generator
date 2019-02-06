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

/*Credit for this function goes to Grom on Stack Overflow:
https://stackoverflow.com/a/17467 */
bool FloatAlmostEqual(float A, float B, int maxUlps)
{
	// Make sure maxUlps is non-negative and small enough that the    
	// default NAN won't compare as equal to anything.    
	assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);
	int aInt = *(int*)&A;
	// Make aInt lexicographically ordered as a twos-complement int    
	if (aInt < 0)
		aInt = 0x80000000 - aInt;
	// Make bInt lexicographically ordered as a twos-complement int    
	int bInt = *(int*)&B;
	if (bInt < 0)
		bInt = 0x80000000 - bInt;
	int intDiff = abs(aInt - bInt);
	if (intDiff <= maxUlps)
		return true;
	return false;
}