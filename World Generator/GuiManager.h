#pragma once
#include "Globals.h"

namespace MapSystem
{
	class MapManager;
}
class ProgramManager;
class GuiManager
{
public:
	GuiManager();
	~GuiManager();

	void Draw(const char* Title, bool* OpenState);

	ProgramManager* Program = nullptr;
	MapSystem::MapManager* MMan = nullptr;
};

