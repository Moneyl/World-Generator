#include "Globals.h"

class StaticTextManager
{
    public:
        StaticTextManager(){};
        ~StaticTextManager(){};

        int AddText();
        void ClearAll();
        void RemoveText(int TextID);
        void SetTextString(int TextID, std::string TextString);
        void SetGlobalTextVariables(int TextSize, sf::Color TextColor, std::string FontLocation);
        std::string GetGlobalFontLocation();
        void SetGlobalFontLocation(std::string FontLocation);

        std::vector <sf::Text*> TextContainer;

        int TotalObjects = 0;
        int CurrentKey = 0;

    private:

        std::string GlobalFontLocation;
        sf::Font GlobalFont;
        int GlobalTextSize;
        sf::Color GlobalTextColor;
};

