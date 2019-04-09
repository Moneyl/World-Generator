#include "GuiManager.h"
#include "ProgramManager.h"

GuiManager::GuiManager()
{

}

GuiManager::~GuiManager()
{

}

void GuiManager::Draw(const char* Title, bool* OpenState)
{
	if(!ImGui::Begin(Title, OpenState))
	{
		ImGui::End();
		return;
	}

	float GuiInputWidth = 230.0f;

	if (ImGui::Button("Generate"))
	{
		if (Program->CurrentState == ProgramManager::WorldGen)
		{
			Program->ResetWorldGen();
			std::cout << "World Generator Reset" << std::endl;
			Program->CommenceWorldGen();
			std::cout << "World Generator Commenced" << std::endl;
		}
	}

	ImGui::Separator();
	ImGui::Text("Height map settings:");
	ImGui::Separator();
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Seed", &MMan->_Seed);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Map width", &MMan->_x);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Map height", &MMan->_y);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Height Octaves", &MMan->_octaves, 0.01f, 0.1f, 3);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Height Persistence", &MMan->_persistence, 0.01f, 0.1f, 3);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Height Scale", &MMan->_scale, 0.01f, 0.1f, 3);
	ImGui::Checkbox("Height turbulence", &MMan->_HeightTurbulence);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Sea level", &MMan->_SeaLevel);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Mountain level", &MMan->_MountainLevel);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Snow level", &MMan->_SnowLevel);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Mountain rate 1", &MMan->_MountainRate1);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Mountain rate 2", &MMan->_MountainRate2);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Land decrease level", &MMan->_LandDecreaseLevel);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Mountain decrease level", &MMan->_MountainDecreaseLevel);

	ImGui::Separator();
	ImGui::Text("Map smoothing settings:");
	ImGui::Separator();
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Corner smooth scale", &MMan->_CornerSmoothScale);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Side smooth scale", &MMan->_SideSmoothScale);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Center smooth scale", &MMan->_CenterSmoothScale);
	ImGui::Checkbox("Do map smoothing", &MMan->_DoMapSmoothing);
	ImGui::Checkbox("Do map side smoothing", &MMan->_DoMapSideSmoothing);

	ImGui::Separator();
	ImGui::Text("Temperature settings:");
	ImGui::Separator();
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Temp low bound", &MMan->_TempLowBound, 1.0f, 10.0f, 3);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Temp high bound", &MMan->_TempHighBound, 1.0f, 10.0f, 3);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Height of equator", &MMan->_HeightOfEquator);

	ImGui::Separator();
	ImGui::Text("Rainfall settings:");
	ImGui::Separator();
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Rainfall divisor", &MMan->_RainfallDivisor);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Rainfall divisor", &MMan->_RainfallOverlapValue);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Rainfall divisor", &MMan->_RainfallOverlapMultiplier);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Base wind rainfall", &MMan->_BaseWindRainfall);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Post mountain wind rainfall", &MMan->_PostMountainWindRainfall);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Post water wind rainfall", &MMan->_PostWaterWindRainfall);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Rainfall increase delta", &MMan->_RainfallIncreaseDelta);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Rainfall decrease delta", &MMan->_RainfallDecreaseDelta);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Rainfall multiplier", &MMan->_RainfallMultiplier);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputFloat("Rainfall noise threshold", &MMan->_RainfallNoiseThreshold);

	ImGui::Separator();
	ImGui::Text("Region settings:");
	ImGui::Separator();
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Minimum water region size", &MMan->_MinimumWaterBodySize);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Number of height region tiers", &MMan->_NumberOfTiers);

	ImGui::Separator();
	ImGui::Text("River settings:");
	ImGui::Separator();
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Number of rivers", &MMan->_NumberOfRivers);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Max rivers", &MMan->_MaxRivers);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Minimum separation distance", &MMan->_MinimumSeparationDistance);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Minimum distance from water", &MMan->_MinimumDistanceFromWater);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Maximum variance", &MMan->_MaximumVariance);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Maximum same move direction", &MMan->_MaximumSameMoveDirection);
	ImGui::Checkbox("Same move restrictions", &MMan->_SameMoveRestrictions);
	ImGui::Checkbox("Direction restrictions", &MMan->_DirectionRestrictions);
	ImGui::PushItemWidth(GuiInputWidth);
	ImGui::InputInt("Min water body target size", &MMan->_MinimumTargetSize);

	ImGui::End();
	return;
}