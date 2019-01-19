#include "StaticTextManager.h"

int StaticTextManager::AddText()
{
    TextContainer.push_back(new sf::Text());
    TextContainer[CurrentKey]->setCharacterSize(GlobalTextSize);
    TextContainer[CurrentKey]->setFillColor(GlobalTextColor);
    TextContainer[CurrentKey]->setFont(GlobalFont);

    CurrentKey++;
    TotalObjects++;
    return CurrentKey - 1;
}

void StaticTextManager::ClearAll()
{
    TextContainer.clear();
}

void StaticTextManager::RemoveText(int TextID)
{

}

void StaticTextManager::SetTextString(int TextID, std::string TextString)
{
    TextContainer[TextID]->setString(TextString);
}

void StaticTextManager::SetGlobalTextVariables(int TextSize, sf::Color TextColor, std::string FontLocation)
{
    GlobalTextSize = TextSize;
    GlobalTextColor = TextColor;
    GlobalFontLocation = FontLocation;
    GlobalFont.loadFromFile(GlobalFontLocation);
}

std::string StaticTextManager::GetGlobalFontLocation()
{
    return GlobalFontLocation;
}

void StaticTextManager::SetGlobalFontLocation(std::string FontLocation)
{
    GlobalFontLocation = FontLocation;
}
