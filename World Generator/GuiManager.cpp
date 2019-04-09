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

	ImGui::PushItemWidth(300.0f);
	ImGui::InputFloat("Height Octaves", &MMan->_octaves, 0.01f, 0.1f, 3);
	ImGui::PushItemWidth(300.0f);
	ImGui::InputFloat("Height Persistence", &MMan->_persistence, 0.01f, 0.1f, 3);
	ImGui::PushItemWidth(300.0f);
	ImGui::InputFloat("Height Scale", &MMan->_scale, 0.01f, 0.1f, 3);

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

	ImGui::End();
	return;
}