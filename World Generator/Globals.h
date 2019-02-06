#include "Files.h"

extern const int MaxUnitsOfLeastPrecision;

std::string GetExePath();
bool DirectoryExists(std::string Directory);
void CreateDirectoryIfNull(std::string Directory);

/*Credit for this function goes to Grom on Stack Overflow:
https://stackoverflow.com/a/17467 */
bool AlmostEqual2sComplement(float A, float B, int maxUlps = MaxUnitsOfLeastPrecision);