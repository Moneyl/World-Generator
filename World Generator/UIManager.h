#include "Files.h"

class ScrollBarControl
{
public:
    ScrollBarControl() {};
    ~ScrollBarControl() {};

    int PreviousScrollbarValue = 0;

    void ScrollPanel(tgui::Panel::Ptr panel, const tgui::Callback& callback)
    {
        int distanceToMove = PreviousScrollbarValue - callback.value;

        // Move all widgets that are inside the panel
        for (auto& widget : panel->getWidgets())
        {
            widget->setPosition(widget->getPosition().x, widget->getPosition().y + distanceToMove);
        }
        PreviousScrollbarValue = callback.value;
    }
};

class UIManager
{
public:
    UIManager() {};
    ~UIManager() {};

	void Initialize(sf::RenderWindow &WindowReference);
	void ConfigureMenus();
	void ConfigureWorldGenSetup();

    //void ConfigureMenusOld();
    //void ConfigureWorldGenSetupOld();

    bool InProgramSettings = 0;
    bool ProgSettingsIsChecked1;

	//Variables
	sf::RenderWindow* CurrentWindow;
	int WindowWidth;
	int WindowHeight;

    std::string ConfigLocation;
    std::string FontLocation;

    sf::Color MenuBackgroundColor;
    sf::Color TextColor;

    tgui::Scrollbar::Ptr WGSScrollbar;

	//UI *** TODO *** Add tooltips at some point ***
	tgui::Gui GameGui;
	tgui::Theme::Ptr GuiTheme;

	tgui::Panel::Ptr MainSettingsPanel;

	tgui::Panel::Ptr MainMenuPanel; //Main menu panel, exit, generate, generate custom, and eventually settings. Perhaps make a helper function for the settings menu.
	tgui::Panel::Ptr WGSPanel; //World gen setup panel, load, save, default, generate, etc.
	tgui::Panel::Ptr WGPanel; //World gen control panel, main menu, back to config, regen, etc. Eventually add additional panels which display more info.

	//Main Menu Start

	tgui::Button::Ptr MainGenerate;
	tgui::Button::Ptr MainGenCustom;
	tgui::Button::Ptr MainSettings;
	tgui::Button::Ptr MainExit;

	//Main Menu End

	//WG Start

	tgui::Label::Ptr WGOverlayLabel;
	tgui::Button::Ptr WGLeftArrow;
	tgui::Button::Ptr WGRightArrow;
	tgui::Button::Ptr WGRegen;
	tgui::Button::Ptr WGConfig;
	tgui::Button::Ptr WGMainMenu;
	tgui::ListBox::Ptr WGListBox;
	tgui::ProgressBar::Ptr WGProgressBar;

	//WG End

	//WGS Controls Start

	tgui::Button::Ptr WGSGenerate;
	tgui::Button::Ptr WGSLoad;
	tgui::Button::Ptr WGSSave;
	tgui::Button::Ptr WGSNew;
	tgui::Button::Ptr WGSMainMenu;

	//WGS Controls End

	//WGS Variables Start

	tgui::TextBox::Ptr WGSProfileName;

	tgui::TextBox::Ptr WGSWidth;
	tgui::TextBox::Ptr WGSHeight;

	tgui::TextBox::Ptr WGSOctaves;
	tgui::TextBox::Ptr WGSPersistence;
	tgui::TextBox::Ptr WGSScale;

	tgui::CheckBox::Ptr WGSMapSmoothing;
	tgui::TextBox::Ptr WGSCornerSmoothScale;
	tgui::TextBox::Ptr WGSSideSmoothScale;
	tgui::TextBox::Ptr WGSCenterSmoothScale;

	tgui::CheckBox::Ptr WGSHeightTurbulence;
	tgui::TextBox::Ptr WGSMountainRate1;
	tgui::TextBox::Ptr WGSMountainRate2;

	tgui::TextBox::Ptr WGSLandDecreaseLevel;
	tgui::TextBox::Ptr WGSMountainDecreaseLevel;

	tgui::TextBox::Ptr WGSBaseRainfall;
	tgui::TextBox::Ptr WGSPostMountainRainfall;
	tgui::TextBox::Ptr WGSPostWaterRainfall;
	
	tgui::TextBox::Ptr WGSRainfallIncreaseDelta;
	tgui::TextBox::Ptr WGSRainfallDecreaseDelta;
	tgui::TextBox::Ptr WGSRainfallMultiplier;

	tgui::TextBox::Ptr WGSRainfallNoiseThreshold;

	tgui::TextBox::Ptr WGSMinimumWaterBodySize;

	tgui::TextBox::Ptr WGSMinimumRiverSeparationDistance;
	tgui::TextBox::Ptr WGSMinimumRiverTargetSize;
	
	//Labels Start
	
	tgui::Label::Ptr WGSLProfileName;

	tgui::Label::Ptr WGSLWidth;
	tgui::Label::Ptr WGSLHeight;

	tgui::Label::Ptr WGSLOctaves;
	tgui::Label::Ptr WGSLPersistence;
	tgui::Label::Ptr WGSLScale;

	tgui::Label::Ptr WGSLMapSmoothing;
	tgui::Label::Ptr WGSLCornerSmoothScale;
	tgui::Label::Ptr WGSLSideSmoothScale;
	tgui::Label::Ptr WGSLCenterSmoothScale;

	tgui::Label::Ptr WGSLHeightTurbulence;
	tgui::Label::Ptr WGSLMountainRate1;
	tgui::Label::Ptr WGSLMountainRate2;

	tgui::Label::Ptr WGSLLandDecreaseLevel;
	tgui::Label::Ptr WGSLMountainDecreaseLevel;

	tgui::Label::Ptr WGSLBaseRainfall;
	tgui::Label::Ptr WGSLPostMountainRainfall;
	tgui::Label::Ptr WGSLPostWaterRainfall;

	tgui::Label::Ptr WGSLRainfallIncreaseDelta;
	tgui::Label::Ptr WGSLRainfallDecreaseDelta;
	tgui::Label::Ptr WGSLRainfallMultiplier;

	tgui::Label::Ptr WGSLRainfallNoiseThreshold;

	tgui::Label::Ptr WGSLMinimumWaterBodySize;

	tgui::Label::Ptr WGSLMinimumRiverSeparationDistance;
	tgui::Label::Ptr WGSLMinimumRiverTargetSize;
	
	//Labels End

	//WGS Variables End

	/// = BROKEN, WANT TO KEEP
	// = Remove, check for any usage in code.

	//Make sure to make variables a constant when necessary.

	//float _amplitude = 1;

	//int _SeedType = 0; Only need seed variable, check for variable use in code.

	//bool _DoMapSideSmoothing = 0;

	//float _TempLowBound = 273.3; //Both in Kelvin
	//float _TempHighBound = 318.15;

	//float _TempRange;
	//float _TempChangeDelta;

	///int _HeightOfEquator = 2; // Preferably an even number to make the equator look nice

	///float _RainfallDivisor = 4; Check Usage
	//float _RainfallOverlapValue = 70;
	//float _RainfallOverlapMultiplier = 4;

	///int _SeaLevel = 130; //COLORING IS BROKEN ON ALL THREE. CHANGE CODE TO ADJUST COLOR DELTA BASED ON HOW FAR SEPARATED MOUNTAIN, SEA, AND SNOW LEVEL ARE
	///int _MountainLevel = 190;
	///int _SnowLevel = 212;

	///FIGURE OUT WHAT MAKES POLES GREY SOMETIMES
	///SEEMS TO ONLY HAPPEN IN THE NORTHWEST CORNER, MAY BE RELATED TO WEATHER SYSTEMS STILL RUNNING FOR SOME REASON

	///int _Seed; Seems broken. Not producing same result with supposedly same seed. Seed may be getting unintentionally reset

	//Water Regions:

	//Height Regions:

	///int _NumberOfTiers = 8; Coloring is broken for higher numbers. Perhaps make a constant.

	//Rivers:

	///int _NumberOfRivers = 120; Try to fix number of dropped rivers, and go over river code in general
	//int _CurrentRiver;

	///int _MinLength; Decide if either variable is needed
	///int _MaxLength;

	//int _MinWidth;
	//int _MaxWidth;

	///int _MaxRivers = 120; FIGURE OUT WHICH OF THESE TWO RIVER # VARIABLES ARE NEEDED, SHOULDN'T NEED BOTH

	//int _MinimumDistanceFromWater = 6; Keep constant

	//int _LastMoveDirection;
	///int _MaximumVariance = 10;
	///int _MaximumSameMoveDirection = 7;

	///bool _SameMoveRestrictions = 0; Determine if needed, see if it decreases dropped river count.
	//bool _DirectionRestrictions = 0; Determine if still needed.
	
	///Following three not needed until weather systems implemented
	//float _CurrentCount = .01;
	//float _Modifier = .01;
	//int _WeatherSystemsToRun = 150;

	///FIX DEFAULT WORLD FILE TO HAVE THE CORRECT VALUES, ALSO FIX 'NEW' BUTTON TO DO THE SAME

private:

};
/*
sf::Texture MenuBackgroundTexture;
sf::Texture BackgroundTexture;
sf::Sprite BackgroundSprite;

tgui::CheckBox::Ptr SettingsCheckBox1;

tgui::Panel::Ptr WorldGenSetupForm;
tgui::Panel::Ptr WGS2;

tgui::Grid::Ptr WGS2Grid;
tgui::Button::Ptr WGS2Save;
tgui::Button::Ptr WGS2Load;
tgui::Button::Ptr WGS2Generate;
tgui::Button::Ptr WGS2MainMenu;
tgui::Button::Ptr WGS2New;

tgui::Button::Ptr SettingsCancelButton;
tgui::Button::Ptr SettingsSaveButton;

tgui::Button::Ptr MenuButton1;
tgui::Button::Ptr MenuButton2;
tgui::Button::Ptr MenuButton3;
tgui::Button::Ptr MainSettingsButton;

tgui::Button::Ptr Play;
tgui::Button::Ptr BackToMain;
tgui::Button::Ptr BackToSetup;
tgui::Button::Ptr RunNewSeed;
tgui::Button::Ptr WorldGenSave;

tgui::Borders DefaultBorder1;
tgui::Borders Border2;
tgui::Borders Border3;
tgui::Borders Border4;
tgui::Borders Border5;
tgui::Borders Border6;
tgui::Borders Border7;
tgui::Borders Border8;
tgui::Borders Border9;
tgui::Borders Border10;

tgui::Panel::Ptr MainMenuForm;
tgui::Panel::Ptr ProgramSettingsForm;
tgui::Panel::Ptr WorldGenForm;

tgui::Grid::Ptr WorldGenSetupGrid;

tgui::Panel::Ptr WG2;
tgui::Grid::Ptr WG2Grid;

tgui::ListBox::Ptr WorldGenLogBox;

tgui::Grid::Ptr MainMenuGrid;
tgui::Grid::Ptr SettingsGrid;

tgui::TextBox::Ptr WGSMapHeight;
tgui::TextBox::Ptr WGSMapWidth;
tgui::TextBox::Ptr WGSProfileName;
tgui::TextBox::Ptr WGSOctaves;
tgui::TextBox::Ptr WGSPersistence;

tgui::TextBox::Ptr WGSScale;
tgui::TextBox::Ptr WGSCornerSmoothScale;
tgui::TextBox::Ptr WGSSideSmoothScale;
tgui::TextBox::Ptr WGSCenterSmoothScale;
tgui::TextBox::Ptr WGSSeedType;

tgui::CheckBox::Ptr WGSDoMapSmoothing;
tgui::CheckBox::Ptr WGSDoMapSideSmoothing;
tgui::TextBox::Ptr WGSTempLowBound;
tgui::TextBox::Ptr WGSTempHighBound;
tgui::TextBox::Ptr WGSHeightOfEquator;

tgui::TextBox::Ptr WGSRainfallDivisor;
tgui::TextBox::Ptr WGSRainfallOverlapValue;
tgui::TextBox::Ptr WGSRainfallOverlapMultiplier;
tgui::TextBox::Ptr WGSBaseWindRainfall;
tgui::TextBox::Ptr WGSPostMountainRainfall;

tgui::TextBox::Ptr WGSPostWaterRainfall;
tgui::TextBox::Ptr WGSRainfallIncreaseDelta;
tgui::TextBox::Ptr WGSRainfallDecreaseDelta;
tgui::TextBox::Ptr WGSRainfallMultiplier;
tgui::TextBox::Ptr WGSMountainRate1;

tgui::TextBox::Ptr WGSMountainRate2;
tgui::TextBox::Ptr WGSLandDecreaseLevel;
tgui::TextBox::Ptr WGSMountainDecreaseLevel;
tgui::TextBox::Ptr WGSRainfallNoiseThreshold;
tgui::CheckBox::Ptr WGSHeightTurbulence;

tgui::TextBox::Ptr WGSSeaLevel;
tgui::TextBox::Ptr WGSMountainLevel;
tgui::TextBox::Ptr WGSSnowLevel;
tgui::TextBox::Ptr WGSMinimumWaterBodySize;
tgui::TextBox::Ptr WGSNumberOfHeightTiers;

tgui::TextBox::Ptr WGSMinimumSeparationDistance;
tgui::TextBox::Ptr WGSMaximumRivers;
tgui::TextBox::Ptr WGSMaximumVariance;
tgui::TextBox::Ptr WGSMaximumSameMoveDirection;
tgui::CheckBox::Ptr WGSSameMoveRestrictions;

tgui::CheckBox::Ptr WGSDirectionRestrictions;
tgui::TextBox::Ptr WGSMinimumTargetSize;


//LABELS//

tgui::Label::Ptr lWGSTitle;

tgui::Label::Ptr lWGSMapHeight;
tgui::Label::Ptr lWGSMapWidth;
tgui::Label::Ptr lWGSProfileName;
tgui::Label::Ptr lWGSOctaves;
tgui::Label::Ptr lWGSPersistence;

tgui::Label::Ptr lWGSScale;
tgui::Label::Ptr lWGSCornerSmoothScale;
tgui::Label::Ptr lWGSSideSmoothScale;
tgui::Label::Ptr lWGSCenterSmoothScale;
tgui::Label::Ptr lWGSSeedType;

tgui::Label::Ptr lWGSDoMapSmoothing;
tgui::Label::Ptr lWGSDoMapSideSmoothing;
tgui::Label::Ptr lWGSTempLowBound;
tgui::Label::Ptr lWGSTempHighBound;
tgui::Label::Ptr lWGSHeightOfEquator;

tgui::Label::Ptr lWGSRainfallDivisor;
tgui::Label::Ptr lWGSRainfallOverlapValue;
tgui::Label::Ptr lWGSRainfallOverlapMultiplier;
tgui::Label::Ptr lWGSBaseWindRainfall;
tgui::Label::Ptr lWGSPostMountainRainfall;

tgui::Label::Ptr lWGSPostWaterRainfall;
tgui::Label::Ptr lWGSRainfallIncreaseDelta;
tgui::Label::Ptr lWGSRainfallDecreaseDelta;
tgui::Label::Ptr lWGSRainfallMultiplier;
tgui::Label::Ptr lWGSMountainRate1;

tgui::Label::Ptr lWGSMountainRate2;
tgui::Label::Ptr lWGSLandDecreaseLevel;
tgui::Label::Ptr lWGSMountainDecreaseLevel;
tgui::Label::Ptr lWGSRainfallNoiseThreshold;
tgui::Label::Ptr lWGSHeightTurbulence;

tgui::Label::Ptr lWGSSeaLevel;
tgui::Label::Ptr lWGSMountainLevel;
tgui::Label::Ptr lWGSSnowLevel;
tgui::Label::Ptr lWGSMinimumWaterBodySize;
tgui::Label::Ptr lWGSNumberOfHeightTiers;

tgui::Label::Ptr lWGSMinimumSeparationDistance;
tgui::Label::Ptr lWGSMaximumRivers;
tgui::Label::Ptr lWGSMaximumVariance;
tgui::Label::Ptr lWGSMaximumSameMoveDirection;
tgui::Label::Ptr lWGSSameMoveRestrictions;

tgui::Label::Ptr lWGSDirectionRestrictions;
tgui::Label::Ptr lWGSMinimumTargetSize;

tgui::Label::Ptr SettingsLabel1;

tgui::Grid::Ptr WorldGenGrid;

tgui::ProgressBar::Ptr WorldGenLoadingBar;*/