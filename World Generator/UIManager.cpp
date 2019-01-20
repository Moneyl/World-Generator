#include "UIManager.h"

void UIManager::Initialize(sf::RenderWindow &WindowReference)
{
	GameGui.setWindow(WindowReference);
	GuiTheme = tgui::Theme::create(ConfigLocation);
	WindowWidth = WindowReference.getSize().x;
	WindowHeight = WindowReference.getSize().y;
}

void UIManager::ConfigureMenus()
{
	try
	{
		//Main Menu Start

		MainMenuPanel = GuiTheme->load("Panel");

		MainGenerate = GuiTheme->load("Button");
		MainGenCustom = GuiTheme->load("Button");
		MainSettings = GuiTheme->load("Button");
		MainExit = GuiTheme->load("Button");

		GameGui.add(MainMenuPanel);

		MainGenerate->setText("Generate World");
		MainGenCustom->setText("Generate Custom World");
		MainSettings->setText("Settings");
		MainExit->setText("Exit");
		
		MainMenuPanel->setBackgroundColor(sf::Color(20, 20, 20));

		MainMenuPanel->setSize("0.1 * parent.w", "0.2 * parent.h");
		MainMenuPanel->setPosition("0.5 * (parent.w - w)", "0.5 * (parent.h - h)");

		MainMenuPanel->add(MainGenerate);
		MainMenuPanel->add(MainGenCustom);
		MainMenuPanel->add(MainSettings);
		MainMenuPanel->add(MainExit);

		MainGenerate->setSize("0.9 * parent.w", "0.2 * parent.h");
		MainGenCustom->setSize("0.9 * parent.w", "0.2 * parent.h");
		MainSettings->setSize("0.9 * parent.w", "0.2 * parent.h");
		MainExit->setSize("0.9 * parent.w", "0.2 * parent.h");
		
		MainGenerate->setPosition("0.5 * (parent.w - w)", "0.04 * parent.h");
		MainGenCustom->setPosition("0.5 * (parent.w - w)", "0.28 * parent.h");
		MainSettings->setPosition("0.5 * (parent.w - w)", "0.52 * parent.h");
		MainExit->setPosition("0.5 * (parent.w - w)", "0.76 * parent.h");

		MainGenerate->setTextSize(14);
		MainGenCustom->setTextSize(14);
		MainSettings->setTextSize(14);
		MainExit->setTextSize(14);
		
		//Main Menu End

		//Main Settings Start

		MainSettingsPanel = GuiTheme->load("Panel");
		GameGui.add(MainSettingsPanel);

		//Main Settings End

		//World Gen Start

		WGPanel = GuiTheme->load("Panel");

		WGOverlayLabel = GuiTheme->load("Label");
		WGLeftArrow = GuiTheme->load("Button");
		WGRightArrow = GuiTheme->load("Button");
		WGRegen = GuiTheme->load("Button");
		WGConfig = GuiTheme->load("Button");
		WGMainMenu = GuiTheme->load("Button");
		WGListBox = GuiTheme->load("Listbox");
		WGProgressBar = GuiTheme->load("ProgressBar");

		GameGui.add(WGPanel);

		WGOverlayLabel->setText("Overlay");
		WGLeftArrow->setText("<");
		WGRightArrow->setText(">");
		WGRegen->setText("Regenerate");
		WGConfig->setText("Configure");
		WGMainMenu->setText("Main Menu");

		WGPanel->setBackgroundColor(sf::Color(20, 20, 20));

		WGPanel->setSize("0.6 * parent.w", "0.35 * parent.h");
		WGPanel->setPosition("0.0", "0.65 * parent.h");

		WGPanel->add(WGOverlayLabel);
		WGPanel->add(WGLeftArrow);
		WGPanel->add(WGRightArrow);
		WGPanel->add(WGRegen);
		WGPanel->add(WGConfig);
		WGPanel->add(WGMainMenu);
		WGPanel->add(WGListBox);
		WGPanel->add(WGProgressBar);
		
		WGLeftArrow->setSize("0.1 * parent.h", "0.1 * parent.h");
		WGRightArrow->setSize("0.1 * parent.h", "0.1 * parent.h");
		WGRegen->setSize("0.07 * parent.w", "0.1 * parent.h");
		WGConfig->setSize("0.07 * parent.w", "0.1 * parent.h");
		WGMainMenu->setSize("0.07 * parent.w", "0.1 * parent.h");
		WGListBox->setSize("0.7 * parent.w", "0.8 * parent.h");
		WGProgressBar->setSize("0.7 * parent.w", "0.1 * parent.h");

		WGOverlayLabel->setPosition("0.5 * (0.06 * parent.w)", "0.04 * parent.h");
		WGLeftArrow->setPosition("0.01 * parent.w", "0.10 * parent.h");
		WGRightArrow->setPosition("(0.08 * parent.w) - w", "0.10 * parent.h");
		WGRegen->setPosition("0.01 * parent.w", "0.22 * parent.h");
		WGConfig->setPosition("0.01 * parent.w", "0.34 * parent.h");
		WGMainMenu->setPosition("0.01 * parent.w", "0.46 * parent.h");
		WGListBox->setPosition("0.5 * (parent.w - w + 0.08 * parent.w)", "0.16 * parent.h");
		WGProgressBar->setPosition("0.5 * (parent.w - w + 0.08 * parent.w)", "0.04 * parent.h");

		WGOverlayLabel->setTextSize(14);
		WGLeftArrow->setTextSize(14);
		WGRightArrow->setTextSize(14);
		WGRegen->setTextSize(14);
		WGConfig->setTextSize(14);
		WGMainMenu->setTextSize(14);
		WGListBox->setTextSize(14);
		WGProgressBar->setTextSize(14);
		
		WGListBox->setAutoScroll(1);

		WGProgressBar->setMinimum(0);

		//World Gen End

	}
	catch (const tgui::Exception& Exception)
	{
		std::cout << "TGUI Exception: " << Exception.what() << std::endl;
	}
}

void UIManager::ConfigureWorldGenSetup()
{
	WGSPanel = GuiTheme->load("Panel");
	GameGui.add(WGSPanel);

	WGSScrollbar = GuiTheme->load("Scrollbar");

	//WGS Controls Start

	WGSPanel->setBackgroundColor(sf::Color(20, 20, 20));
	
	WGSPanel->setSize("0.9 * parent.w", "0.9 * parent.h");
	WGSPanel->setPosition("0.5 * (parent.w - w)", "0.5 * (parent.h - h)");
	
	WGSPanel->add(WGSScrollbar);
	WGSScrollbar->setSize("w", "parent.h");
	WGSScrollbar->setPosition("parent.w - w", 0);

	WGSGenerate = GuiTheme->load("Button");
	WGSLoad = GuiTheme->load("Button");
	WGSSave = GuiTheme->load("Button");
	WGSNew = GuiTheme->load("Button");
	WGSMainMenu = GuiTheme->load("Button");
	WGSGenerate->setText("Generate");
	WGSLoad->setText("Load");
	WGSSave->setText("Save");
	WGSNew->setText("New");
	WGSMainMenu->setText("Main Menu");

	WGSPanel->add(WGSGenerate);
	WGSPanel->add(WGSLoad);
	WGSPanel->add(WGSSave);
	WGSPanel->add(WGSNew);
	WGSPanel->add(WGSMainMenu);

	WGSGenerate->setSize("0.05 * parent.w", "0.04 * parent.h");
	WGSLoad->setSize("0.05 * parent.w", "0.04 * parent.h");
	WGSSave->setSize("0.05 * parent.w", "0.04 * parent.h");
	WGSNew->setSize("0.05 * parent.w", "0.04 * parent.h");
	WGSMainMenu->setSize("0.05 * parent.w", "0.04 * parent.h");

	WGSGenerate->setPosition("0.01 * parent.w ", "0.02 * parent.h");
	WGSLoad->setPosition("0.01 * parent.w ", "0.07 * parent.h");
	WGSSave->setPosition("0.01 * parent.w", "0.12 * parent.h");
	WGSNew->setPosition("0.01 * parent.w", "0.17 * parent.h");
	WGSMainMenu->setPosition("0.01 * parent.w", "0.22 * parent.h");

	WGSGenerate->setTextSize(14);
	WGSLoad->setTextSize(14);
	WGSSave->setTextSize(14);
	WGSNew->setTextSize(14);
	WGSMainMenu->setTextSize(14);

	//WGS Controls End

	//WGS Variables Start

	WGSProfileName = GuiTheme->load("TextBox");
	WGSWidth = GuiTheme->load("TextBox");
	WGSHeight = GuiTheme->load("TextBox");
	WGSOctaves = GuiTheme->load("TextBox");
	WGSPersistence = GuiTheme->load("TextBox");
	WGSScale = GuiTheme->load("TextBox");
	WGSMapSmoothing = GuiTheme->load("CheckBox");
	WGSCornerSmoothScale = GuiTheme->load("TextBox");
	WGSSideSmoothScale = GuiTheme->load("TextBox");
	WGSCenterSmoothScale = GuiTheme->load("TextBox");
	WGSHeightTurbulence = GuiTheme->load("CheckBox");
	WGSMountainRate1 = GuiTheme->load("TextBox");
	WGSMountainRate2 = GuiTheme->load("TextBox");
	WGSLandDecreaseLevel = GuiTheme->load("TextBox");
	WGSMountainDecreaseLevel = GuiTheme->load("TextBox");
	WGSBaseRainfall = GuiTheme->load("TextBox");
	WGSPostMountainRainfall = GuiTheme->load("TextBox");
	WGSPostWaterRainfall = GuiTheme->load("TextBox");
	WGSRainfallIncreaseDelta = GuiTheme->load("TextBox");
	WGSRainfallDecreaseDelta = GuiTheme->load("TextBox");
	WGSRainfallMultiplier = GuiTheme->load("TextBox");
	WGSRainfallNoiseThreshold = GuiTheme->load("TextBox");
	WGSMinimumWaterBodySize = GuiTheme->load("TextBox");
	WGSMinimumRiverSeparationDistance = GuiTheme->load("TextBox");
	WGSMinimumRiverTargetSize = GuiTheme->load("TextBox");

	

	WGSLProfileName = GuiTheme->load("Label");
	WGSLWidth = GuiTheme->load("Label");
	WGSLHeight = GuiTheme->load("Label");
	WGSLOctaves = GuiTheme->load("Label");
	WGSLPersistence = GuiTheme->load("Label");
	WGSLScale = GuiTheme->load("Label");
	WGSLMapSmoothing = GuiTheme->load("Label");
	WGSLCornerSmoothScale = GuiTheme->load("Label");
	WGSLSideSmoothScale = GuiTheme->load("Label");
	WGSLCenterSmoothScale = GuiTheme->load("Label");
	WGSLHeightTurbulence = GuiTheme->load("Label");
	WGSLMountainRate1 = GuiTheme->load("Label");
	WGSLMountainRate2 = GuiTheme->load("Label");
	WGSLLandDecreaseLevel = GuiTheme->load("Label");
	WGSLMountainDecreaseLevel = GuiTheme->load("Label");
	WGSLBaseRainfall = GuiTheme->load("Label");
	WGSLPostMountainRainfall = GuiTheme->load("Label");
	WGSLPostWaterRainfall = GuiTheme->load("Label");
	WGSLRainfallIncreaseDelta = GuiTheme->load("Label");
	WGSLRainfallDecreaseDelta = GuiTheme->load("Label");
	WGSLRainfallMultiplier = GuiTheme->load("Label");
	WGSLRainfallNoiseThreshold = GuiTheme->load("Label");
	WGSLMinimumWaterBodySize = GuiTheme->load("Label");
	WGSLMinimumRiverSeparationDistance = GuiTheme->load("Label");
	WGSLMinimumRiverTargetSize = GuiTheme->load("Label");



	WGSLProfileName->setText("Profile Name:");
	WGSLWidth->setText("Map Width:");
	WGSLHeight->setText("Map Height:");
	WGSLOctaves->setText("Octaves:");
	WGSLPersistence->setText("Persistence:");
	WGSLScale->setText("Scale:");
	WGSLMapSmoothing->setText("Map Smoothing:");
	WGSLCornerSmoothScale->setText("Corner Smooth Scale:");
	WGSLSideSmoothScale->setText("Side Smooth Scale:");
	WGSLCenterSmoothScale->setText("Center Smooth Scale:");
	WGSLHeightTurbulence->setText("Height Turbulence:");
	WGSLMountainRate1->setText("Mountain Rate 1:");
	WGSLMountainRate2->setText("Mountain Rate 2:");
	WGSLLandDecreaseLevel->setText("Land Decrease Level:");
	WGSLMountainDecreaseLevel->setText("Mountain Decrease Level");
	WGSLBaseRainfall->setText("Base Rainfall:");
	WGSLPostMountainRainfall->setText("Post Mountain Rainfall:");
	WGSLPostWaterRainfall->setText("Post Water Rainfall:");
	WGSLRainfallIncreaseDelta->setText("Rainfall Increase Delta:");
	WGSLRainfallDecreaseDelta->setText("Rainfall Decrease Delta:");
	WGSLRainfallMultiplier->setText("Rainfall Multiplier:");
	WGSLRainfallNoiseThreshold->setText("Rainfall Noise Threshold:");
	WGSLMinimumWaterBodySize->setText("Minimum Water Body Size:");
	WGSLMinimumRiverSeparationDistance->setText("Minimum River Separation Distance:");
	WGSLMinimumRiverTargetSize->setText("Minimum River Target Size:");



	WGSPanel->add(WGSProfileName);
	WGSPanel->add(WGSWidth);
	WGSPanel->add(WGSHeight);
	WGSPanel->add(WGSOctaves);
	WGSPanel->add(WGSPersistence);
	WGSPanel->add(WGSScale);
	WGSPanel->add(WGSMapSmoothing);
	WGSPanel->add(WGSCornerSmoothScale);
	WGSPanel->add(WGSSideSmoothScale);
	WGSPanel->add(WGSCenterSmoothScale);
	WGSPanel->add(WGSHeightTurbulence);
	WGSPanel->add(WGSMountainRate1);
	WGSPanel->add(WGSMountainRate2);
	WGSPanel->add(WGSLandDecreaseLevel);
	WGSPanel->add(WGSMountainDecreaseLevel);
	WGSPanel->add(WGSBaseRainfall);
	WGSPanel->add(WGSPostMountainRainfall);
	WGSPanel->add(WGSPostWaterRainfall);
	WGSPanel->add(WGSRainfallIncreaseDelta);
	WGSPanel->add(WGSRainfallDecreaseDelta);
	WGSPanel->add(WGSRainfallMultiplier);
	WGSPanel->add(WGSRainfallNoiseThreshold);
	WGSPanel->add(WGSMinimumWaterBodySize);
	WGSPanel->add(WGSMinimumRiverSeparationDistance);
	WGSPanel->add(WGSMinimumRiverTargetSize);



	WGSPanel->add(WGSLProfileName);
	WGSPanel->add(WGSLWidth);
	WGSPanel->add(WGSLHeight);
	WGSPanel->add(WGSLOctaves);
	WGSPanel->add(WGSLPersistence);
	WGSPanel->add(WGSLScale);
	WGSPanel->add(WGSLMapSmoothing);
	WGSPanel->add(WGSLCornerSmoothScale);
	WGSPanel->add(WGSLSideSmoothScale);
	WGSPanel->add(WGSLCenterSmoothScale);
	WGSPanel->add(WGSLHeightTurbulence);
	WGSPanel->add(WGSLMountainRate1);
	WGSPanel->add(WGSLMountainRate2);
	WGSPanel->add(WGSLLandDecreaseLevel);
	WGSPanel->add(WGSLMountainDecreaseLevel);
	WGSPanel->add(WGSLBaseRainfall);
	WGSPanel->add(WGSLPostMountainRainfall);
	WGSPanel->add(WGSLPostWaterRainfall);
	WGSPanel->add(WGSLRainfallIncreaseDelta);
	WGSPanel->add(WGSLRainfallDecreaseDelta);
	WGSPanel->add(WGSLRainfallMultiplier);
	WGSPanel->add(WGSLRainfallNoiseThreshold);
	WGSPanel->add(WGSLMinimumWaterBodySize);
	WGSPanel->add(WGSLMinimumRiverSeparationDistance);
	WGSPanel->add(WGSLMinimumRiverTargetSize);

	

	WGSProfileName->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSWidth->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSHeight->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSOctaves->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSPersistence->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSScale->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSMapSmoothing->setSize("0.02 * parent.w", "0.03 * parent.h");//
	WGSCornerSmoothScale->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSSideSmoothScale->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSCenterSmoothScale->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSHeightTurbulence->setSize("0.02 * parent.w", "0.03 * parent.h");//
	WGSMountainRate1->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSMountainRate2->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSLandDecreaseLevel->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSMountainDecreaseLevel->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSBaseRainfall->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSPostMountainRainfall->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSPostWaterRainfall->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSRainfallIncreaseDelta->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSRainfallDecreaseDelta->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSRainfallMultiplier->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSRainfallNoiseThreshold->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSMinimumWaterBodySize->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSMinimumRiverSeparationDistance->setSize("0.1 * parent.w", "0.03 * parent.h");
	WGSMinimumRiverTargetSize->setSize("0.1 * parent.w", "0.03 * parent.h");


	WGSProfileName->setPosition("0.88 * parent.w ", "0.02 * parent.h");
	WGSWidth->setPosition("0.88 * parent.w ", "0.055 * parent.h");
	WGSHeight->setPosition("0.88 * parent.w ", "0.09 * parent.h");
	WGSOctaves->setPosition("0.88 * parent.w ", "0.125 * parent.h");
	WGSPersistence->setPosition("0.88 * parent.w ", "0.16 * parent.h");
	WGSScale->setPosition("0.88 * parent.w ", "0.195 * parent.h");
	WGSMapSmoothing->setPosition("0.92 * parent.w ", "0.23 * parent.h");//
	WGSCornerSmoothScale->setPosition("0.88 * parent.w ", "0.265 * parent.h");
	WGSSideSmoothScale->setPosition("0.88 * parent.w ", "0.30 * parent.h");
	WGSCenterSmoothScale->setPosition("0.88 * parent.w ", "0.335 * parent.h");
	WGSHeightTurbulence->setPosition("0.92 * parent.w ", "0.37 * parent.h");//
	WGSMountainRate1->setPosition("0.88 * parent.w ", "0.405 * parent.h");
	WGSMountainRate2->setPosition("0.88 * parent.w ", "0.44 * parent.h");
	WGSLandDecreaseLevel->setPosition("0.88 * parent.w ", "0.475 * parent.h");
	WGSMountainDecreaseLevel->setPosition("0.88 * parent.w ", "0.51 * parent.h");
	WGSBaseRainfall->setPosition("0.88 * parent.w ", "0.545 * parent.h");
	WGSPostMountainRainfall->setPosition("0.88 * parent.w ", "0.58 * parent.h");
	WGSPostWaterRainfall->setPosition("0.88 * parent.w ", "0.615 * parent.h");
	WGSRainfallIncreaseDelta->setPosition("0.88 * parent.w ", "0.65 * parent.h");
	WGSRainfallDecreaseDelta->setPosition("0.88 * parent.w ", "0.685 * parent.h");
	WGSRainfallMultiplier->setPosition("0.88 * parent.w ", "0.72 * parent.h");
	WGSRainfallNoiseThreshold->setPosition("0.88 * parent.w ", "0.755 * parent.h");
	WGSMinimumWaterBodySize->setPosition("0.88 * parent.w ", "0.79 * parent.h");
	WGSMinimumRiverSeparationDistance->setPosition("0.88 * parent.w ", "0.825 * parent.h");
	WGSMinimumRiverTargetSize->setPosition("0.88 * parent.w ", "0.86 * parent.h");



	WGSLProfileName->setPosition("0.7 * parent.w ", "0.02 * parent.h");
	WGSLWidth->setPosition("0.7 * parent.w ", "0.055 * parent.h");
	WGSLHeight->setPosition("0.7 * parent.w ", "0.09 * parent.h");
	WGSLOctaves->setPosition("0.7 * parent.w ", "0.125 * parent.h");
	WGSLPersistence->setPosition("0.7 * parent.w ", "0.16 * parent.h");
	WGSLScale->setPosition("0.7 * parent.w ", "0.195 * parent.h");
	WGSLMapSmoothing->setPosition("0.7 * parent.w ", "0.23 * parent.h");
	WGSLCornerSmoothScale->setPosition("0.7 * parent.w ", "0.265 * parent.h");
	WGSLSideSmoothScale->setPosition("0.7 * parent.w ", "0.30 * parent.h");
	WGSLCenterSmoothScale->setPosition("0.7 * parent.w ", "0.335 * parent.h");
	WGSLHeightTurbulence->setPosition("0.7 * parent.w ", "0.37 * parent.h");
	WGSLMountainRate1->setPosition("0.7 * parent.w ", "0.405 * parent.h");
	WGSLMountainRate2->setPosition("0.7 * parent.w ", "0.44 * parent.h");
	WGSLLandDecreaseLevel->setPosition("0.7 * parent.w ", "0.475 * parent.h");
	WGSLMountainDecreaseLevel->setPosition("0.7 * parent.w ", "0.51 * parent.h");
	WGSLBaseRainfall->setPosition("0.7 * parent.w ", "0.545 * parent.h");
	WGSLPostMountainRainfall->setPosition("0.7 * parent.w ", "0.58 * parent.h");
	WGSLPostWaterRainfall->setPosition("0.7 * parent.w ", "0.615 * parent.h");
	WGSLRainfallIncreaseDelta->setPosition("0.7 * parent.w ", "0.65 * parent.h");
	WGSLRainfallDecreaseDelta->setPosition("0.7 * parent.w ", "0.685 * parent.h");
	WGSLRainfallMultiplier->setPosition("0.7 * parent.w ", "0.72 * parent.h");
	WGSLRainfallNoiseThreshold->setPosition("0.7 * parent.w ", "0.755 * parent.h");
	WGSLMinimumWaterBodySize->setPosition("0.7 * parent.w ", "0.79 * parent.h");
	WGSLMinimumRiverSeparationDistance->setPosition("0.7 * parent.w ", "0.825 * parent.h");
	WGSLMinimumRiverTargetSize->setPosition("0.7 * parent.w ", "0.86 * parent.h");



	WGSProfileName->setTextSize(14);
	WGSWidth->setTextSize(14);
	WGSHeight->setTextSize(14);
	WGSOctaves->setTextSize(14);
	WGSPersistence->setTextSize(14);
	WGSScale->setTextSize(14);
	WGSMapSmoothing->setTextSize(14);
	WGSCornerSmoothScale->setTextSize(14);
	WGSSideSmoothScale->setTextSize(14);
	WGSCenterSmoothScale->setTextSize(14);
	WGSHeightTurbulence->setTextSize(14);
	WGSMountainRate1->setTextSize(14);
	WGSMountainRate2->setTextSize(14);
	WGSLandDecreaseLevel->setTextSize(14);
	WGSMountainDecreaseLevel->setTextSize(14);
	WGSBaseRainfall->setTextSize(14);
	WGSPostMountainRainfall->setTextSize(14);
	WGSPostWaterRainfall->setTextSize(14);
	WGSRainfallIncreaseDelta->setTextSize(14);
	WGSRainfallDecreaseDelta->setTextSize(14);
	WGSRainfallMultiplier->setTextSize(14);
	WGSRainfallNoiseThreshold->setTextSize(14);
	WGSMinimumWaterBodySize->setTextSize(14);
	WGSMinimumRiverSeparationDistance->setTextSize(14);
	WGSMinimumRiverTargetSize->setTextSize(14);


	WGSLProfileName->setTextSize(14);
	WGSLWidth->setTextSize(14);
	WGSLHeight->setTextSize(14);
	WGSLOctaves->setTextSize(14);
	WGSLPersistence->setTextSize(14);
	WGSLScale->setTextSize(14);
	WGSLMapSmoothing->setTextSize(14);
	WGSLCornerSmoothScale->setTextSize(14);
	WGSLSideSmoothScale->setTextSize(14);
	WGSLCenterSmoothScale->setTextSize(14);
	WGSLHeightTurbulence->setTextSize(14);
	WGSLMountainRate1->setTextSize(14);
	WGSLMountainRate2->setTextSize(14);
	WGSLLandDecreaseLevel->setTextSize(14);
	WGSLMountainDecreaseLevel->setTextSize(14);
	WGSLBaseRainfall->setTextSize(14);
	WGSLPostMountainRainfall->setTextSize(14);
	WGSLPostWaterRainfall->setTextSize(14);
	WGSLRainfallIncreaseDelta->setTextSize(14);
	WGSLRainfallDecreaseDelta->setTextSize(14);
	WGSLRainfallMultiplier->setTextSize(14);
	WGSLRainfallNoiseThreshold->setTextSize(14);
	WGSLMinimumWaterBodySize->setTextSize(14);
	WGSLMinimumRiverSeparationDistance->setTextSize(14);
	WGSLMinimumRiverTargetSize->setTextSize(14);

	/*
	WGSProfileName;
	WGSWidth;
	WGSHeight;
	WGSOctaves;
	WGSPersistence;
	WGSScale;
	WGSMapSmoothing;
	WGSCornerSmoothScale;
	WGSSideSmoothScale;
	WGSCenterSmoothScale;
	WGSHeightTurbulence;
	WGSMountainRate1;
	WGSMountainRate2;
	WGSLandDecreaseLevel;
	WGSMountainDecreaseLevel;
	WGSBaseRainfall;
	WGSPostMountainRainfall;
	WGSPostWaterRainfall;
	WGSRainfallIncreaseDelta;
	WGSRainfallDecreaseDelta;
	WGSRainfallMultiplier;
	WGSRainfallNoiseThreshold;
	WGSMinimumWaterBodySize;
	WGSMinimumRiverSeparationDistance;
	WGSMinimumRiverTargetSize;
	*/

	/*WGSGenerate->setSize("0.05 * parent.w", "0.04 * parent.h");
	WGSLoad->setSize("0.05 * parent.w", "0.04 * parent.h");
	WGSSave->setSize("0.05 * parent.w", "0.04 * parent.h");
	WGSNew->setSize("0.05 * parent.w", "0.04 * parent.h");
	WGSMainMenu->setSize("0.05 * parent.w", "0.04 * parent.h");

	WGSGenerate->setPosition("0.01 * parent.w ", "0.02 * parent.h");
	WGSLoad->setPosition("0.01 * parent.w ", "0.07 * parent.h");
	WGSSave->setPosition("0.01 * parent.w", "0.12 * parent.h");
	WGSNew->setPosition("0.01 * parent.w", "0.17 * parent.h");
	WGSMainMenu->setPosition("0.01 * parent.w", "0.22 * parent.h");

	WGSGenerate->setTextSize(14);
	WGSLoad->setTextSize(14);
	WGSSave->setTextSize(14);
	WGSNew->setTextSize(14);
	WGSMainMenu->setTextSize(14);*/

	//WGS Variables End
}
/*
void UIManager::ConfigureMenusOld()
{
	GameGui.setWindow(*CurrentWindow);
	GameGui.setFont(FontLocation);
	GuiTheme = tgui::Theme::create(ConfigLocation);// Try this: "../../widgets/Black.txt"

	MenuBackgroundColor.r = 112;
	MenuBackgroundColor.g = 112;
	MenuBackgroundColor.b = 112;
	MenuBackgroundColor.a = 255;

	TextColor.r = 225;
	TextColor.g = 174;
	TextColor.b = 51;
	TextColor.a = 255;

	DefaultBorder1.bottom = 10;
	DefaultBorder1.top = 22;
	DefaultBorder1.left = 33;
	DefaultBorder1.right = 32;

	Border2.bottom = 0;
	Border2.top = 0;
	Border2.left = 0;
	Border2.right = 0;

	Border3.bottom = 10;
	Border3.top = 408;
	Border3.left = 62;
	Border3.right = 0;

	Border4.bottom = 10;
	Border4.top = 408;
	Border4.left = 0;
	Border4.right = 0;

	Border5.bottom = 10;
	Border5.top = 22;
	Border5.left = 25;
	Border5.right = 0;

	Border6.bottom = 10;
	Border6.top = 25;
	Border6.left = 15;
	Border6.right = 0;

	Border7.bottom = 10;
	Border7.top = 15;
	Border7.left = 33;
	Border7.right = 32;

	Border8.bottom = 10;
	Border8.top = 8;
	Border8.left = 40;
	Border8.right = 35;

	Border9.top = 8;
	Border9.bottom = 8;
	Border9.left = 0;
	Border9.right = 0;

	Border10.top = 0;
	Border10.bottom = 10;
	Border10.left = 13;
	Border10.right = 13;

	GameGui.add(MainMenuForm, "MainMenuForm");
	GameGui.add(WorldGenSetupForm, "WorldGenSetupForm");
	GameGui.add(ProgramSettingsForm, "ProgramSettingsForm");
	GameGui.add(WGS2, "WorldGenSetupForm2");
	GameGui.add(WorldGenForm, "WorldGenForm");
	GameGui.add(WGSScrollbar, "WorldGenSetupScrollbar");
	GameGui.add(WG2, "WorldGenForm2");

	MainMenuForm->add(MainMenuGrid, "MainMenuGrid");
	MainMenuForm->add(MenuButton1, "MainButton1");
	MainMenuForm->add(MenuButton2, "MainButton2");
	MainMenuForm->add(MenuButton3, "MainButton3");

	WorldGenForm->add(WorldGenGrid, "WorldGenGrid");
	WorldGenForm->add(WorldGenLoadingBar, "WorldGenLoadingBar");
	WorldGenForm->add(WorldGenLogBox, "WorldGenLogBox");

	WG2->add(WG2Grid, "WG2Grid");
	WG2->add(BackToMain, "BackToMain");
	WG2->add(BackToSetup, "BackToSetup");
	WG2->add(RunNewSeed, "RunNewSeed");

	MenuBackgroundTexture.loadFromFile("WindowBackground6.png");
	BackgroundTexture.loadFromFile("Background2.png");

	BackgroundSprite.setTexture(BackgroundTexture);
	BackgroundSprite.setPosition(0, 0);

	MainMenuForm->setSize(300, 350);
	MainMenuForm->setPosition(30, 700);
	MainMenuForm->setBackgroundColor(MenuBackgroundColor);
	//MainMenuForm->setBackgroundTexture(&MenuBackgroundTexture);

	ProgramSettingsForm->setSize(500, 500);
	ProgramSettingsForm->setPosition(300, 250);
	ProgramSettingsForm->setBackgroundColor(MenuBackgroundColor);
	//ProgramSettingsForm->setBackgroundTexture(&MenuBackgroundTexture);

	WorldGenForm->setSize(752, 300);
	WorldGenForm->setPosition(248, 700);
	WorldGenForm->setBackgroundColor(MenuBackgroundColor);
	//WorldGenForm->setBackgroundTexture(&MenuBackgroundTexture);

	WG2->setSize(200, 300);
	WG2->setPosition(24, 700);
	WG2->setBackgroundColor(MenuBackgroundColor);
	//WG2->setBackgroundTexture(&MenuBackgroundTexture);

	WorldGenLoadingBar = GuiTheme->load("ProgressBar");
	WorldGenLoadingBar->setSize(726, 30);
	WorldGenLoadingBar->setPosition(37, 700);
	WorldGenLoadingBar->setMinimum(0);
	WorldGenLoadingBar->setMaximum(12);
	WorldGenLoadingBar->setTextSize(16);
	//WorldGenLoadingBar->setTextColor(sf::Color(0,0,0,255));

	WorldGenLogBox = GuiTheme->load("ListBox");
	WorldGenLogBox->setSize(726, 250);
	WorldGenLogBox->setPosition(37, 740);
	//WorldGenLogBox->setTextColor(sf::Color::Blue);

	BackToMain = GuiTheme->load("Button");
	BackToMain->setSize(200, 30);
	BackToMain->setText("Back to main menu");
	BackToMain->setTextSize(12);

	BackToSetup = GuiTheme->load("Button");
	BackToSetup->setSize(200, 30);
	BackToSetup->setText("Back to setup");
	BackToSetup->setTextSize(12);

	RunNewSeed = GuiTheme->load("Button");
	RunNewSeed->setSize(200, 30);
	RunNewSeed->setText("Generate with new seed");
	RunNewSeed->setTextSize(12);

	MenuButton1 = GuiTheme->load("Button");
	MenuButton1->setSize(300, 30);
	MenuButton1->setPosition(35, 25);
	MenuButton1->setText("Generate Random World");
	MenuButton1->setTextSize(16);

	MenuButton2 = GuiTheme->load("Button");
	MenuButton2->setSize(300, 30);
	MenuButton2->setPosition(35, 75);
	MenuButton2->setText("Generate Custom World");
	MenuButton2->setTextSize(16);

	MenuButton3 = GuiTheme->load("Button");
	MenuButton3->setSize(300, 30);
	MenuButton3->setPosition(80, 175);
	MenuButton3->setText("Exit");
	MenuButton3->setTextSize(16);

	int EditBoxXSize = 120;
	int EditBoxYSize = 30;
	int EditBoxTextSize = 16;

	int CheckBoxXSize = 30;
	int CheckBoxYSize = 30;

	//WorldGenLogBox->setTextColor(TextColor);

	/*MenuButton1->bindCallback(tgui::Button::LeftMouseClicked);
	MenuButton1->setCallbackId(1);
	MenuButton2->bindCallback(tgui::Button::LeftMouseClicked);
	MenuButton2->setCallbackId(2);
	MenuButton3->bindCallback(tgui::Button::LeftMouseClicked);
	MenuButton3->setCallbackId(3);

	WGS2Generate->bindCallback(tgui::Button::LeftMouseClicked);
	WGS2Generate->setCallbackId(10);
	WGS2MainMenu->bindCallback(tgui::Button::LeftMouseClicked);
	WGS2MainMenu->setCallbackId(11);
	WGS2New->bindCallback(tgui::Button::LeftMouseClicked);
	WGS2New->setCallbackId(12);

	BackToMain->bindCallback(tgui::Button::LeftMouseClicked);
	BackToMain->setCallbackId(13);
	BackToSetup->bindCallback(tgui::Button::LeftMouseClicked);
	BackToSetup->setCallbackId(14);
	RunNewSeed->bindCallback(tgui::Button::LeftMouseClicked);
	RunNewSeed->setCallbackId(15);

	MainMenuGrid->addWidget(MenuButton1, 1, 2);
	MainMenuGrid->addWidget(MenuButton2, 2, 2);
	MainMenuGrid->addWidget(MenuButton3, 3, 2);

	/*MainMenuGrid->changeWidgetLayout(MenuButton1, tgui::Grid::Layout::Up);
	MainMenuGrid->changeWidgetLayout(MenuButton2, tgui::Grid::Layout::Center);
	MainMenuGrid->changeWidgetLayout(MenuButton3, tgui::Grid::Layout::Bottom);

	MainMenuGrid->changeWidgetBorders(MenuButton1, Border2);
	MainMenuGrid->changeWidgetBorders(MenuButton2, Border2);
	MainMenuGrid->changeWidgetBorders(MenuButton3, Border2);

	WorldGenGrid->addWidget(WorldGenLoadingBar, 1, 1);
	WorldGenGrid->addWidget(WorldGenLogBox, 2, 1);

	WG2Grid->addWidget(BackToMain, 1, 1);
	WG2Grid->addWidget(BackToSetup, 2, 1);
	WG2Grid->addWidget(RunNewSeed, 3, 1);

	WorldGenGrid->changeWidgetBorders(WorldGenLoadingBar, Border10);
	WorldGenGrid->changeWidgetBorders(WorldGenLogBox, Border10);
}

void UIManager::ConfigureWorldGenSetupOld()
{
	int EditBoxXSize = 120;
	int EditBoxYSize = 30;
	int EditBoxTextSize = 16;

	int CheckBoxXSize = 30;
	int CheckBoxYSize = 30;

	WorldGenSetupForm->add(WorldGenSetupGrid, "WorldGenSetupGrid");

	WorldGenSetupForm->add(WGSMapWidth, "WGSMapWidth");
	WorldGenSetupForm->add(WGSMapHeight, "WGSMapHeight");
	WorldGenSetupForm->add(WGSProfileName, "WGSProfileName");
	WorldGenSetupForm->add(WGSOctaves, "WGSOctaves");
	WorldGenSetupForm->add(WGSPersistence, "WGSPersistence");

	WorldGenSetupForm->add(WGSScale, "WGSScale");
	WorldGenSetupForm->add(WGSCornerSmoothScale, "WGSCornerSmoothScale");
	WorldGenSetupForm->add(WGSSideSmoothScale, "WGSSideSmoothScale");
	WorldGenSetupForm->add(WGSCenterSmoothScale, "WGSCenterSmoothScale");
	WorldGenSetupForm->add(WGSSeedType, "WGSSeedType");

	WorldGenSetupForm->add(WGSDoMapSmoothing, "WGSDoMapSmoothing");
	WorldGenSetupForm->add(WGSDoMapSideSmoothing, "WGSDoMapSmoothing");
	WorldGenSetupForm->add(WGSTempLowBound, "WGSTempLowBound");
	WorldGenSetupForm->add(WGSTempHighBound, "WGSTempHighBound");
	WorldGenSetupForm->add(WGSHeightOfEquator, "WGSHeightOfEquator");

	WorldGenSetupForm->add(WGSRainfallDivisor, "WGSRainfallDivisor");
	WorldGenSetupForm->add(WGSRainfallOverlapValue, "WGSRainfallOverlapValue");
	WorldGenSetupForm->add(WGSRainfallOverlapMultiplier, "WGSRainfallOverlapMultiplier");
	WorldGenSetupForm->add(WGSBaseWindRainfall, "WGSBaseWindRainfall");
	WorldGenSetupForm->add(WGSPostMountainRainfall, "WGSPostMountainRainfall");

	WorldGenSetupForm->add(WGSPostWaterRainfall, "WGSPostWaterRainfall");
	WorldGenSetupForm->add(WGSRainfallIncreaseDelta, "WGSRainfallIncreaseDelta");
	WorldGenSetupForm->add(WGSRainfallDecreaseDelta, "WGSRainfallDecreaseDelta");
	WorldGenSetupForm->add(WGSRainfallMultiplier, "WGSRainfallMultiplier");
	WorldGenSetupForm->add(WGSMountainRate1, "WGSMountainRate1");

	WorldGenSetupForm->add(WGSMountainRate2, "WGSMountainRate2");
	WorldGenSetupForm->add(WGSLandDecreaseLevel, "WGSLandDecreaseLevel");
	WorldGenSetupForm->add(WGSMountainDecreaseLevel, "WGSMountainDecreaseLevel");
	WorldGenSetupForm->add(WGSRainfallNoiseThreshold, "WGSRainfallNoiseThreshold");
	WorldGenSetupForm->add(WGSHeightTurbulence, "WGSHeightTurbulence");

	WorldGenSetupForm->add(WGSSeaLevel, "WGSSeaLevel");
	WorldGenSetupForm->add(WGSMountainLevel, "WGSMountainLevel");
	WorldGenSetupForm->add(WGSSnowLevel, "WGSSnowLevel");
	WorldGenSetupForm->add(WGSMinimumWaterBodySize, "WGSMinimumWaterBodySize");
	WorldGenSetupForm->add(WGSNumberOfHeightTiers, "WGSNumberOfHeightTiers");

	WorldGenSetupForm->add(WGSMinimumSeparationDistance, "WGSMinimumSeparateDistance");
	WorldGenSetupForm->add(WGSMaximumRivers, "WGSMaximumRivers");
	WorldGenSetupForm->add(WGSMaximumVariance, "WGSMaximumVariance");
	WorldGenSetupForm->add(WGSMaximumSameMoveDirection, "WGSMaximumSameMoveDirection");
	WorldGenSetupForm->add(WGSSameMoveRestrictions, "WGSSameMoveRestrictions");

	WorldGenSetupForm->add(WGSDirectionRestrictions, "WGSDirectionRestrictions");
	WorldGenSetupForm->add(WGSMinimumTargetSize, "WGSMinimumTargetSize");


	//LABELS//

	WorldGenSetupForm->add(lWGSTitle, "lWGSTitle");

	WorldGenSetupForm->add(lWGSMapWidth, "WGSMapWidth");
	WorldGenSetupForm->add(lWGSMapHeight, "WGSMapHeight");
	WorldGenSetupForm->add(lWGSProfileName, "WGSProfileName");
	WorldGenSetupForm->add(lWGSOctaves, "WGSOctaves");
	WorldGenSetupForm->add(lWGSPersistence, "WGSPersistence");

	WorldGenSetupForm->add(lWGSScale, "WGSScale");
	WorldGenSetupForm->add(lWGSCornerSmoothScale, "WGSCornerSmoothScale");
	WorldGenSetupForm->add(lWGSSideSmoothScale, "WGSSideSmoothScale");
	WorldGenSetupForm->add(lWGSCenterSmoothScale, "WGSCenterSmoothScale");
	WorldGenSetupForm->add(lWGSSeedType, "WGSSeedType");

	WorldGenSetupForm->add(lWGSDoMapSmoothing, "WGSDoMapSmoothing");
	WorldGenSetupForm->add(lWGSDoMapSideSmoothing, "WGSDoMapSmoothing");
	WorldGenSetupForm->add(lWGSTempLowBound, "WGSTempLowBound");
	WorldGenSetupForm->add(lWGSTempHighBound, "WGSTempHighBound");
	WorldGenSetupForm->add(lWGSHeightOfEquator, "WGSHeightOfEquator");

	WorldGenSetupForm->add(lWGSRainfallDivisor, "WGSRainfallDivisor");
	WorldGenSetupForm->add(lWGSRainfallOverlapValue, "WGSRainfallOverlapValue");
	WorldGenSetupForm->add(lWGSRainfallOverlapMultiplier, "WGSRainfallOverlapMultiplier");
	WorldGenSetupForm->add(lWGSBaseWindRainfall, "WGSBaseWindRainfall");
	WorldGenSetupForm->add(lWGSPostMountainRainfall, "WGSPostMountainRainfall");

	WorldGenSetupForm->add(lWGSPostWaterRainfall, "WGSPostWaterRainfall");
	WorldGenSetupForm->add(lWGSRainfallIncreaseDelta, "WGSRainfallIncreaseDelta");
	WorldGenSetupForm->add(lWGSRainfallDecreaseDelta, "WGSRainfallDecreaseDelta");
	WorldGenSetupForm->add(lWGSRainfallMultiplier, "WGSRainfallMultiplier");
	WorldGenSetupForm->add(lWGSMountainRate1, "WGSMountainRate1");

	WorldGenSetupForm->add(lWGSMountainRate2, "WGSMountainRate2");
	WorldGenSetupForm->add(lWGSLandDecreaseLevel, "WGSLandDecreaseLevel");
	WorldGenSetupForm->add(lWGSMountainDecreaseLevel, "WGSMountainDecreaseLevel");
	WorldGenSetupForm->add(lWGSRainfallNoiseThreshold, "WGSRainfallNoiseThreshold");
	WorldGenSetupForm->add(lWGSHeightTurbulence, "WGSHeightTurbulence");

	WorldGenSetupForm->add(lWGSSeaLevel, "WGSSeaLevel");
	WorldGenSetupForm->add(lWGSMountainLevel, "WGSMountainLevel");
	WorldGenSetupForm->add(lWGSSnowLevel, "WGSSnowLevel");
	WorldGenSetupForm->add(lWGSMinimumWaterBodySize, "WGSMinimumWaterBodySize");
	WorldGenSetupForm->add(lWGSNumberOfHeightTiers, "WGSNumberOfHeightTiers");

	WorldGenSetupForm->add(lWGSMinimumSeparationDistance, "WGSMinimumSeparateDistance");
	WorldGenSetupForm->add(lWGSMaximumRivers, "WGSMaximumRivers");
	WorldGenSetupForm->add(lWGSMaximumVariance, "WGSMaximumVariance");
	WorldGenSetupForm->add(lWGSMaximumSameMoveDirection, "WGSMaximumSameMoveDirection");
	WorldGenSetupForm->add(lWGSSameMoveRestrictions, "WGSSameMoveRestrictions");

	WorldGenSetupForm->add(lWGSDirectionRestrictions, "WGSDirectionRestrictions");
	WorldGenSetupForm->add(lWGSMinimumTargetSize, "WGSMinimumTargetSize");

	WGS2->add(WGS2Grid, "WorldGenSetupForm2Grid");
	WGS2->add(WGS2Save, "WorldGenSetupForm2Save");
	WGS2->add(WGS2Load, "WorldGenSetupForm2Load");
	WGS2->add(WGS2Generate, "WorldGenSetupForm2Generate");
	WGS2->add(WGS2MainMenu, "WorldGenSetupForm2MainMenu");
	WGS2->add(WGS2New, "WorldGenSetupForm2New");

	WorldGenSetupForm->setSize(700, 700);
	WorldGenSetupForm->setPosition(250, 100);
	WorldGenSetupForm->setBackgroundColor(MenuBackgroundColor);
	//WorldGenSetupForm->setBackgroundTexture(&MenuBackgroundTexture);

	WGS2->setSize(200, 350);
	WGS2->setPosition(25, 100);
	WGS2->setBackgroundColor(MenuBackgroundColor);
	//WGS2->setBackgroundTexture(&MenuBackgroundTexture);

	WGS2Save = GuiTheme->load("Button");
	WGS2Save->setSize(200, 30);
	WGS2Save->setPosition(750, 650);
	WGS2Save->setText("Save");
	WGS2Save->setTextSize(16);

	WGS2Load = GuiTheme->load("Button");
	WGS2Load->setSize(200, 30);
	WGS2Load->setPosition(750, 650);
	WGS2Load->setText("Load");
	WGS2Load->setTextSize(16);

	WGS2Generate = GuiTheme->load("Button");
	WGS2Generate->setSize(200, 30);
	WGS2Generate->setPosition(750, 650);
	WGS2Generate->setText("Generate");
	WGS2Generate->setTextSize(16);

	WGS2MainMenu = GuiTheme->load("Button");
	WGS2MainMenu->setSize(200, 30);
	WGS2MainMenu->setPosition(750, 650);
	WGS2MainMenu->setText("Main Menu");
	WGS2MainMenu->setTextSize(16);

	WGS2New = GuiTheme->load("Button");
	WGS2New->setSize(200, 30);
	WGS2New->setPosition(750, 650);
	WGS2New->setText("New");
	WGS2New->setTextSize(16);

	WGSProfileName = GuiTheme->load("TextBox");
	WGSProfileName->setSize(EditBoxXSize, EditBoxYSize);
	WGSProfileName->setTextSize(EditBoxTextSize);

	WGSMapHeight = GuiTheme->load("TextBox");
	WGSMapHeight->setSize(EditBoxXSize, EditBoxYSize);
	WGSMapHeight->setTextSize(EditBoxTextSize);

	WGSMapWidth = GuiTheme->load("TextBox");
	WGSMapWidth->setSize(EditBoxXSize, EditBoxYSize);
	WGSMapWidth->setTextSize(EditBoxTextSize);

	WGSOctaves = GuiTheme->load("TextBox");
	WGSOctaves->setSize(EditBoxXSize, EditBoxYSize);
	WGSOctaves->setTextSize(EditBoxTextSize);

	WGSPersistence = GuiTheme->load("TextBox");
	WGSPersistence->setSize(EditBoxXSize, EditBoxYSize);
	WGSPersistence->setTextSize(EditBoxTextSize);

	WGSScale = GuiTheme->load("TextBox");
	WGSScale->setSize(EditBoxXSize, EditBoxYSize);
	WGSScale->setTextSize(EditBoxTextSize);

	WGSCornerSmoothScale = GuiTheme->load("TextBox");
	WGSCornerSmoothScale->setSize(EditBoxXSize, EditBoxYSize);
	WGSCornerSmoothScale->setTextSize(EditBoxTextSize);

	WGSSideSmoothScale = GuiTheme->load("TextBox");
	WGSSideSmoothScale->setSize(EditBoxXSize, EditBoxYSize);
	WGSSideSmoothScale->setTextSize(EditBoxTextSize);

	WGSCenterSmoothScale = GuiTheme->load("TextBox");
	WGSCenterSmoothScale->setSize(EditBoxXSize, EditBoxYSize);
	WGSCenterSmoothScale->setTextSize(EditBoxTextSize);

	WGSSeedType = GuiTheme->load("TextBox");
	WGSSeedType->setSize(EditBoxXSize, EditBoxYSize);
	WGSSeedType->setTextSize(EditBoxTextSize);

	WGSDoMapSmoothing = GuiTheme->load("TextBox");
	WGSDoMapSmoothing->setSize(CheckBoxXSize, CheckBoxYSize);

	WGSDoMapSideSmoothing = GuiTheme->load("TextBox");
	WGSDoMapSideSmoothing->setSize(CheckBoxXSize, CheckBoxYSize);

	WGSTempLowBound = GuiTheme->load("TextBox");
	WGSTempLowBound->setSize(EditBoxXSize, EditBoxYSize);
	WGSTempLowBound->setTextSize(EditBoxTextSize);

	WGSTempHighBound = GuiTheme->load("TextBox");
	WGSTempHighBound->setSize(EditBoxXSize, EditBoxYSize);
	WGSTempHighBound->setTextSize(EditBoxTextSize);

	WGSHeightOfEquator = GuiTheme->load("TextBox");
	WGSHeightOfEquator->setSize(EditBoxXSize, EditBoxYSize);
	WGSHeightOfEquator->setTextSize(EditBoxTextSize);

	WGSRainfallDivisor = GuiTheme->load("TextBox");
	WGSRainfallDivisor->setSize(EditBoxXSize, EditBoxYSize);
	WGSRainfallDivisor->setTextSize(EditBoxTextSize);

	WGSRainfallOverlapValue = GuiTheme->load("TextBox");
	WGSRainfallOverlapValue->setSize(EditBoxXSize, EditBoxYSize);
	WGSRainfallOverlapValue->setTextSize(EditBoxTextSize);

	WGSRainfallOverlapMultiplier = GuiTheme->load("TextBox");
	WGSRainfallOverlapMultiplier->setSize(EditBoxXSize, EditBoxYSize);
	WGSRainfallOverlapMultiplier->setTextSize(EditBoxTextSize);

	WGSBaseWindRainfall = GuiTheme->load("TextBox");
	WGSBaseWindRainfall->setSize(EditBoxXSize, EditBoxYSize);
	WGSBaseWindRainfall->setTextSize(EditBoxTextSize);

	WGSPostMountainRainfall = GuiTheme->load("TextBox");
	WGSPostMountainRainfall->setSize(EditBoxXSize, EditBoxYSize);
	WGSPostMountainRainfall->setTextSize(EditBoxTextSize);

	WGSPostWaterRainfall = GuiTheme->load("TextBox");
	WGSPostWaterRainfall->setSize(EditBoxXSize, EditBoxYSize);
	WGSPostWaterRainfall->setTextSize(EditBoxTextSize);

	WGSRainfallIncreaseDelta = GuiTheme->load("TextBox");
	WGSRainfallIncreaseDelta->setSize(EditBoxXSize, EditBoxYSize);
	WGSRainfallIncreaseDelta->setTextSize(EditBoxTextSize);

	WGSRainfallDecreaseDelta = GuiTheme->load("TextBox");
	WGSRainfallDecreaseDelta->setSize(EditBoxXSize, EditBoxYSize);
	WGSRainfallDecreaseDelta->setTextSize(EditBoxTextSize);

	WGSRainfallMultiplier = GuiTheme->load("TextBox");
	WGSRainfallMultiplier->setSize(EditBoxXSize, EditBoxYSize);
	WGSRainfallMultiplier->setTextSize(EditBoxTextSize);

	WGSMountainRate1 = GuiTheme->load("TextBox");
	WGSMountainRate1->setSize(EditBoxXSize, EditBoxYSize);
	WGSMountainRate1->setTextSize(EditBoxTextSize);

	WGSMountainRate2 = GuiTheme->load("TextBox");
	WGSMountainRate2->setSize(EditBoxXSize, EditBoxYSize);
	WGSMountainRate2->setTextSize(EditBoxTextSize);

	WGSLandDecreaseLevel = GuiTheme->load("TextBox");
	WGSLandDecreaseLevel->setSize(EditBoxXSize, EditBoxYSize);
	WGSLandDecreaseLevel->setTextSize(EditBoxTextSize);

	WGSMountainDecreaseLevel = GuiTheme->load("TextBox");
	WGSMountainDecreaseLevel->setSize(EditBoxXSize, EditBoxYSize);
	WGSMountainDecreaseLevel->setTextSize(EditBoxTextSize);

	WGSRainfallNoiseThreshold = GuiTheme->load("TextBox");
	WGSRainfallNoiseThreshold->setSize(EditBoxXSize, EditBoxYSize);
	WGSRainfallNoiseThreshold->setTextSize(EditBoxTextSize);

	WGSHeightTurbulence = GuiTheme->load("TextBox");
	WGSHeightTurbulence->setSize(CheckBoxXSize, CheckBoxYSize);

	WGSSeaLevel = GuiTheme->load("TextBox");
	WGSSeaLevel->setSize(EditBoxXSize, EditBoxYSize);
	WGSSeaLevel->setTextSize(EditBoxTextSize);

	WGSMountainLevel = GuiTheme->load("TextBox");
	WGSMountainLevel->setSize(EditBoxXSize, EditBoxYSize);
	WGSMountainLevel->setTextSize(EditBoxTextSize);

	WGSSnowLevel = GuiTheme->load("TextBox");
	WGSSnowLevel->setSize(EditBoxXSize, EditBoxYSize);
	WGSSnowLevel->setTextSize(EditBoxTextSize);

	WGSMinimumWaterBodySize = GuiTheme->load("TextBox");
	WGSMinimumWaterBodySize->setSize(EditBoxXSize, EditBoxYSize);
	WGSMinimumWaterBodySize->setTextSize(EditBoxTextSize);

	WGSNumberOfHeightTiers = GuiTheme->load("TextBox");
	WGSNumberOfHeightTiers->setSize(EditBoxXSize, EditBoxYSize);
	WGSNumberOfHeightTiers->setTextSize(EditBoxTextSize);

	WGSMinimumSeparationDistance = GuiTheme->load("TextBox");
	WGSMinimumSeparationDistance->setSize(EditBoxXSize, EditBoxYSize);
	WGSMinimumSeparationDistance->setTextSize(EditBoxTextSize);

	WGSMaximumRivers = GuiTheme->load("TextBox");
	WGSMaximumRivers->setSize(EditBoxXSize, EditBoxYSize);
	WGSMaximumRivers->setTextSize(EditBoxTextSize);

	WGSMaximumVariance = GuiTheme->load("TextBox");
	WGSMaximumVariance->setSize(EditBoxXSize, EditBoxYSize);
	WGSMaximumVariance->setTextSize(EditBoxTextSize);

	WGSMaximumSameMoveDirection = GuiTheme->load("TextBox");
	WGSMaximumSameMoveDirection->setSize(EditBoxXSize, EditBoxYSize);
	WGSMaximumSameMoveDirection->setTextSize(EditBoxTextSize);

	WGSSameMoveRestrictions = GuiTheme->load("TextBox");
	WGSSameMoveRestrictions->setSize(CheckBoxXSize, CheckBoxYSize);

	WGSDirectionRestrictions = GuiTheme->load("TextBox");
	WGSDirectionRestrictions->setSize(CheckBoxXSize, CheckBoxYSize);

	WGSMinimumTargetSize = GuiTheme->load("TextBox");
	WGSMinimumTargetSize->setSize(EditBoxXSize, EditBoxYSize);
	WGSMinimumTargetSize->setTextSize(EditBoxTextSize);

	lWGSProfileName->setTextSize(EditBoxTextSize);
	lWGSProfileName->setText("Parameter Set Name:");

	lWGSTitle->setTextSize(20);
	lWGSTitle->setText("Custom World Generation Setup:");
	lWGSTitle->setTextColor(TextColor);

	lWGSMapHeight->setTextSize(EditBoxTextSize);
	lWGSMapHeight->setText("Map Height:");

	lWGSMapWidth->setTextSize(EditBoxTextSize);
	lWGSMapWidth->setText("Map Width:");

	lWGSOctaves->setTextSize(EditBoxTextSize);
	lWGSOctaves->setText("Octaves:");

	lWGSPersistence->setTextSize(EditBoxTextSize);
	lWGSPersistence->setText("Persistence:");

	lWGSScale->setTextSize(EditBoxTextSize);
	lWGSScale->setText("Scale:");

	lWGSCornerSmoothScale->setTextSize(EditBoxTextSize);
	lWGSCornerSmoothScale->setText("Corner Smooth Scale:");

	lWGSSideSmoothScale->setTextSize(EditBoxTextSize);
	lWGSSideSmoothScale->setText("Side Smooth Scale:");

	lWGSCenterSmoothScale->setTextSize(EditBoxTextSize);
	lWGSCenterSmoothScale->setText("Center Smooth Scale:");

	lWGSSeedType->setTextSize(EditBoxTextSize);
	lWGSDoMapSideSmoothing->setText("Map Side Smoothing:");

	lWGSTempLowBound->setTextSize(EditBoxTextSize);
	lWGSTempLowBound->setText("Temperature Low Bound:");

	lWGSTempHighBound->setTextSize(EditBoxTextSize);
	lWGSTempHighBound->setText("Temperature");

	lWGSRainfallDivisor->setTextSize(EditBoxTextSize);
	lWGSSeedType->setText("Seed:");

	lWGSDoMapSmoothing->setTextSize(EditBoxTextSize);
	lWGSDoMapSmoothing->setText("Map Smoothing:");

	lWGSDoMapSideSmoothing->setTextSize(EditBoxTextSize);
	lWGSDoMapSideSmoothing->setText("Map Side Smoothing:");

	lWGSTempLowBound->setTextSize(EditBoxTextSize);
	lWGSTempLowBound->setText("Temperature Low Bound:");

	lWGSTempHighBound->setTextSize(EditBoxTextSize);
	lWGSTempHighBound->setText("Temperature High Bound:");

	lWGSHeightOfEquator->setTextSize(EditBoxTextSize);
	lWGSHeightOfEquator->setText("Equator Height:");

	lWGSRainfallDivisor->setTextSize(EditBoxTextSize);
	lWGSRainfallDivisor->setText("Rainfall Divisor:");

	lWGSRainfallOverlapValue->setTextSize(EditBoxTextSize);
	lWGSRainfallOverlapValue->setText("Rainfall Overlap Value:");

	lWGSRainfallOverlapMultiplier->setTextSize(EditBoxTextSize);
	lWGSRainfallOverlapMultiplier->setText("Rainfall Overlap Multiplier:");

	lWGSBaseWindRainfall->setTextSize(EditBoxTextSize);
	lWGSBaseWindRainfall->setText("Base Wind Rainfall:");

	lWGSPostMountainRainfall->setTextSize(EditBoxTextSize);
	lWGSPostMountainRainfall->setText("Post Mountain Rainfall:");

	lWGSPostWaterRainfall->setTextSize(EditBoxTextSize);
	lWGSPostWaterRainfall->setText("Post Water Rainfall:");

	lWGSRainfallIncreaseDelta->setTextSize(EditBoxTextSize);
	lWGSRainfallIncreaseDelta->setText("Rainfall Increase Delta:");

	lWGSRainfallDecreaseDelta->setTextSize(EditBoxTextSize);
	lWGSRainfallDecreaseDelta->setText("Rainfall Decrease Delta:");

	lWGSRainfallMultiplier->setTextSize(EditBoxTextSize);
	lWGSRainfallMultiplier->setText("Rainfall Multiplier:");

	lWGSMountainRate1->setTextSize(EditBoxTextSize);
	lWGSMountainRate1->setText("Mountain Rate One:");

	lWGSMountainRate2->setTextSize(EditBoxTextSize);
	lWGSMountainRate2->setText("Mountain Rate Two:");

	lWGSLandDecreaseLevel->setTextSize(EditBoxTextSize);
	lWGSLandDecreaseLevel->setText("Land Decrease Level:");

	lWGSMountainDecreaseLevel->setTextSize(EditBoxTextSize);
	lWGSMountainDecreaseLevel->setText("Mountain Decrease Level:");

	lWGSRainfallNoiseThreshold->setTextSize(EditBoxTextSize);
	lWGSRainfallNoiseThreshold->setText("Rainfall Noise Threshold:");

	lWGSHeightTurbulence->setTextSize(EditBoxTextSize);
	lWGSHeightTurbulence->setText("Height Turbulence:");

	lWGSSeaLevel->setTextSize(EditBoxTextSize);
	lWGSSeaLevel->setText("Sea Level:");

	lWGSMountainLevel->setTextSize(EditBoxTextSize);
	lWGSMountainLevel->setText("Mountain Level:");

	lWGSSnowLevel->setTextSize(EditBoxTextSize);
	lWGSSnowLevel->setText("Snow Level:");

	lWGSMinimumWaterBodySize->setTextSize(EditBoxTextSize);
	lWGSMinimumWaterBodySize->setText("Minimum Water Body Size:");

	lWGSNumberOfHeightTiers->setTextSize(EditBoxTextSize);
	lWGSNumberOfHeightTiers->setText("# Of Height Tiers:");

	lWGSMinimumSeparationDistance->setTextSize(EditBoxTextSize);
	lWGSMinimumSeparationDistance->setText("River Separation Distance:");

	lWGSMaximumRivers->setTextSize(EditBoxTextSize);
	lWGSMaximumRivers->setText("# Of Rivers:");

	lWGSMaximumVariance->setTextSize(EditBoxTextSize);
	lWGSMaximumVariance->setText("Maximum Variance:");

	lWGSMaximumSameMoveDirection->setTextSize(EditBoxTextSize);
	lWGSMaximumSameMoveDirection->setText("Maximum Same Move Direction:");

	lWGSSameMoveRestrictions->setTextSize(EditBoxTextSize);
	lWGSSameMoveRestrictions->setText("Same Move Restrictions:");

	lWGSDirectionRestrictions->setTextSize(EditBoxTextSize);
	lWGSDirectionRestrictions->setText("Direction Restrictions:");

	lWGSMinimumTargetSize->setTextSize(EditBoxTextSize);
	lWGSMinimumTargetSize->setText("Minimum River Target Size:");

	lWGSProfileName->setTextColor(TextColor);
	lWGSMapHeight->setTextColor(TextColor);
	lWGSMapWidth->setTextColor(TextColor);
	lWGSOctaves->setTextColor(TextColor);
	lWGSPersistence->setTextColor(TextColor);
	lWGSScale->setTextColor(TextColor);
	lWGSCornerSmoothScale->setTextColor(TextColor);
	lWGSSideSmoothScale->setTextColor(TextColor);
	lWGSCenterSmoothScale->setTextColor(TextColor);
	lWGSSeedType->setTextColor(TextColor);
	lWGSDoMapSmoothing->setTextColor(TextColor);
	lWGSDoMapSideSmoothing->setTextColor(TextColor);
	lWGSTempLowBound->setTextColor(TextColor);
	lWGSTempHighBound->setTextColor(TextColor);
	lWGSHeightOfEquator->setTextColor(TextColor);
	lWGSRainfallDivisor->setTextColor(TextColor);
	lWGSRainfallOverlapValue->setTextColor(TextColor);
	lWGSRainfallOverlapMultiplier->setTextColor(TextColor);
	lWGSBaseWindRainfall->setTextColor(TextColor);
	lWGSPostMountainRainfall->setTextColor(TextColor);
	lWGSPostWaterRainfall->setTextColor(TextColor);
	lWGSRainfallIncreaseDelta->setTextColor(TextColor);
	lWGSRainfallDecreaseDelta->setTextColor(TextColor);
	lWGSRainfallMultiplier->setTextColor(TextColor);
	lWGSMountainRate1->setTextColor(TextColor);
	lWGSMountainRate2->setTextColor(TextColor);
	lWGSLandDecreaseLevel->setTextColor(TextColor);
	lWGSMountainDecreaseLevel->setTextColor(TextColor);
	lWGSRainfallNoiseThreshold->setTextColor(TextColor);
	lWGSHeightTurbulence->setTextColor(TextColor);
	lWGSSeaLevel->setTextColor(TextColor);
	lWGSMountainLevel->setTextColor(TextColor);
	lWGSSnowLevel->setTextColor(TextColor);
	lWGSMinimumWaterBodySize->setTextColor(TextColor);
	lWGSNumberOfHeightTiers->setTextColor(TextColor);
	lWGSMinimumSeparationDistance->setTextColor(TextColor);
	lWGSMaximumRivers->setTextColor(TextColor);
	lWGSMaximumVariance->setTextColor(TextColor);
	lWGSMaximumSameMoveDirection->setTextColor(TextColor);
	lWGSSameMoveRestrictions->setTextColor(TextColor);
	lWGSDirectionRestrictions->setTextColor(TextColor);
	lWGSMinimumTargetSize->setTextColor(TextColor);

	WGS2Grid->addWidget(WGS2Generate, 1, 1);
	WGS2Grid->addWidget(WGS2Load, 2, 1);
	WGS2Grid->addWidget(WGS2Save, 3, 1);
	WGS2Grid->addWidget(WGS2New, 4, 1);
	WGS2Grid->addWidget(WGS2MainMenu, 5, 1);

	WGS2Grid->changeWidgetBorders(WGS2Generate, Border2);
	WGS2Grid->changeWidgetBorders(WGS2Load, Border2);
	WGS2Grid->changeWidgetBorders(WGS2Save, Border2);
	WGS2Grid->changeWidgetBorders(WGS2MainMenu, Border2);
	WGS2Grid->changeWidgetBorders(WGS2New, Border2);

	WorldGenSetupGrid->addWidget(lWGSTitle, 1, 1);

	WorldGenSetupGrid->addWidget(WGSProfileName, 2, 2);
	WorldGenSetupGrid->addWidget(WGSMapWidth, 3, 2);
	WorldGenSetupGrid->addWidget(WGSMapHeight, 4, 2);
	WorldGenSetupGrid->addWidget(WGSOctaves, 5, 2);
	WorldGenSetupGrid->addWidget(WGSPersistence, 6, 2);

	WorldGenSetupGrid->addWidget(WGSScale, 7, 2);
	WorldGenSetupGrid->addWidget(WGSCornerSmoothScale, 8, 2);
	WorldGenSetupGrid->addWidget(WGSSideSmoothScale, 9, 2);
	WorldGenSetupGrid->addWidget(WGSCenterSmoothScale, 10, 2);
	WorldGenSetupGrid->addWidget(WGSSeedType, 11, 2);

	WorldGenSetupGrid->addWidget(WGSDoMapSmoothing, 12, 2);
	WorldGenSetupGrid->addWidget(WGSDoMapSideSmoothing, 13, 2);
	WorldGenSetupGrid->addWidget(WGSTempLowBound, 14, 2);
	WorldGenSetupGrid->addWidget(WGSTempHighBound, 15, 2);
	WorldGenSetupGrid->addWidget(WGSHeightOfEquator, 16, 2);

	WorldGenSetupGrid->addWidget(WGSRainfallDivisor, 17, 2);
	WorldGenSetupGrid->addWidget(WGSRainfallOverlapValue, 18, 2);
	WorldGenSetupGrid->addWidget(WGSRainfallOverlapMultiplier, 19, 2);
	WorldGenSetupGrid->addWidget(WGSBaseWindRainfall, 20, 2);
	WorldGenSetupGrid->addWidget(WGSPostMountainRainfall, 21, 2);

	WorldGenSetupGrid->addWidget(WGSPostWaterRainfall, 22, 2);
	WorldGenSetupGrid->addWidget(WGSRainfallIncreaseDelta, 23, 2);
	WorldGenSetupGrid->addWidget(WGSRainfallDecreaseDelta, 24, 2);
	WorldGenSetupGrid->addWidget(WGSRainfallMultiplier, 25, 2);
	WorldGenSetupGrid->addWidget(WGSMountainRate1, 26, 2);

	WorldGenSetupGrid->addWidget(WGSMountainRate2, 27, 2);
	WorldGenSetupGrid->addWidget(WGSLandDecreaseLevel, 28, 2);
	WorldGenSetupGrid->addWidget(WGSMountainDecreaseLevel, 29, 2);
	WorldGenSetupGrid->addWidget(WGSRainfallNoiseThreshold, 30, 2);
	WorldGenSetupGrid->addWidget(WGSHeightTurbulence, 31, 2);

	WorldGenSetupGrid->addWidget(WGSSeaLevel, 32, 2);
	WorldGenSetupGrid->addWidget(WGSMountainLevel, 33, 2);
	WorldGenSetupGrid->addWidget(WGSSnowLevel, 34, 2);
	WorldGenSetupGrid->addWidget(WGSMinimumWaterBodySize, 35, 2);
	WorldGenSetupGrid->addWidget(WGSNumberOfHeightTiers, 36, 2);

	WorldGenSetupGrid->addWidget(WGSMinimumSeparationDistance, 37, 2);
	WorldGenSetupGrid->addWidget(WGSMaximumRivers, 38, 2);
	WorldGenSetupGrid->addWidget(WGSMaximumVariance, 39, 2);
	WorldGenSetupGrid->addWidget(WGSMaximumSameMoveDirection, 40, 2);

	WorldGenSetupGrid->addWidget(WGSDirectionRestrictions, 41, 2);
	WorldGenSetupGrid->addWidget(WGSSameMoveRestrictions, 42, 2);
	WorldGenSetupGrid->addWidget(WGSMinimumTargetSize, 43, 2);

	WorldGenSetupGrid->addWidget(lWGSProfileName, 2, 1);
	WorldGenSetupGrid->addWidget(lWGSMapWidth, 3, 1);
	WorldGenSetupGrid->addWidget(lWGSMapHeight, 4, 1);
	WorldGenSetupGrid->addWidget(lWGSOctaves, 5, 1);
	WorldGenSetupGrid->addWidget(lWGSPersistence, 6, 1);

	WorldGenSetupGrid->addWidget(lWGSScale, 7, 1);
	WorldGenSetupGrid->addWidget(lWGSCornerSmoothScale, 8, 1);
	WorldGenSetupGrid->addWidget(lWGSSideSmoothScale, 9, 1);
	WorldGenSetupGrid->addWidget(lWGSCenterSmoothScale, 10, 1);
	WorldGenSetupGrid->addWidget(lWGSSeedType, 11, 1);

	WorldGenSetupGrid->addWidget(lWGSDoMapSmoothing, 12, 1);
	WorldGenSetupGrid->addWidget(lWGSDoMapSideSmoothing, 13, 1);
	WorldGenSetupGrid->addWidget(lWGSTempLowBound, 14, 1);
	WorldGenSetupGrid->addWidget(lWGSTempHighBound, 15, 1);
	WorldGenSetupGrid->addWidget(lWGSHeightOfEquator, 16, 1);

	WorldGenSetupGrid->addWidget(lWGSRainfallDivisor, 17, 1);
	WorldGenSetupGrid->addWidget(lWGSRainfallOverlapValue, 18, 1);
	WorldGenSetupGrid->addWidget(lWGSRainfallOverlapMultiplier, 19, 1);
	WorldGenSetupGrid->addWidget(lWGSBaseWindRainfall, 20, 1);
	WorldGenSetupGrid->addWidget(lWGSPostMountainRainfall, 21, 1);

	WorldGenSetupGrid->addWidget(lWGSPostWaterRainfall, 22, 1);
	WorldGenSetupGrid->addWidget(lWGSRainfallIncreaseDelta, 23, 1);
	WorldGenSetupGrid->addWidget(lWGSRainfallDecreaseDelta, 24, 1);
	WorldGenSetupGrid->addWidget(lWGSRainfallMultiplier, 25, 1);
	WorldGenSetupGrid->addWidget(lWGSMountainRate1, 26, 1);

	WorldGenSetupGrid->addWidget(lWGSMountainRate2, 27, 1);
	WorldGenSetupGrid->addWidget(lWGSLandDecreaseLevel, 28, 1);
	WorldGenSetupGrid->addWidget(lWGSMountainDecreaseLevel, 29, 1);
	WorldGenSetupGrid->addWidget(lWGSRainfallNoiseThreshold, 30, 1);
	WorldGenSetupGrid->addWidget(lWGSHeightTurbulence, 31, 1);

	WorldGenSetupGrid->addWidget(lWGSSeaLevel, 32, 1);
	WorldGenSetupGrid->addWidget(lWGSMountainLevel, 33, 1);
	WorldGenSetupGrid->addWidget(lWGSSnowLevel, 34, 1);
	WorldGenSetupGrid->addWidget(lWGSMinimumWaterBodySize, 35, 1);
	WorldGenSetupGrid->addWidget(lWGSNumberOfHeightTiers, 36, 1);

	WorldGenSetupGrid->addWidget(lWGSMinimumSeparationDistance, 37, 1);
	WorldGenSetupGrid->addWidget(lWGSMaximumRivers, 38, 1);
	WorldGenSetupGrid->addWidget(lWGSMaximumVariance, 39, 1);
	WorldGenSetupGrid->addWidget(lWGSMaximumSameMoveDirection, 40, 1);

	WorldGenSetupGrid->addWidget(lWGSDirectionRestrictions, 41, 1);
	WorldGenSetupGrid->addWidget(lWGSSameMoveRestrictions, 42, 1);
	WorldGenSetupGrid->addWidget(lWGSMinimumTargetSize, 43, 1);

	WorldGenSetupGrid->changeWidgetBorders(lWGSTitle, Border7);

	WorldGenSetupGrid->changeWidgetBorders(WGSProfileName, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSMapHeight, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSMapWidth, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSOctaves, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSPersistence, Border9);

	WorldGenSetupGrid->changeWidgetBorders(WGSScale, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSCornerSmoothScale, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSSideSmoothScale, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSCenterSmoothScale, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSSeedType, Border9);

	WorldGenSetupGrid->changeWidgetBorders(WGSDoMapSmoothing, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSDoMapSideSmoothing, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSTempLowBound, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSTempHighBound, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSHeightOfEquator, Border9);

	WorldGenSetupGrid->changeWidgetBorders(WGSRainfallDivisor, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSRainfallOverlapValue, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSRainfallOverlapMultiplier, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSBaseWindRainfall, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSPostMountainRainfall, Border9);

	WorldGenSetupGrid->changeWidgetBorders(WGSPostWaterRainfall, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSRainfallIncreaseDelta, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSRainfallDecreaseDelta, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSRainfallMultiplier, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSMountainRate1, Border9);

	WorldGenSetupGrid->changeWidgetBorders(WGSMountainRate2, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSLandDecreaseLevel, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSMountainDecreaseLevel, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSRainfallNoiseThreshold, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSHeightTurbulence, Border9);

	WorldGenSetupGrid->changeWidgetBorders(WGSSeaLevel, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSMountainLevel, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSSnowLevel, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSMinimumWaterBodySize, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSNumberOfHeightTiers, Border9);

	WorldGenSetupGrid->changeWidgetBorders(WGSMinimumSeparationDistance, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSMaximumRivers, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSMaximumVariance, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSMaximumSameMoveDirection, Border9);

	WorldGenSetupGrid->changeWidgetBorders(WGSSameMoveRestrictions, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSDirectionRestrictions, Border9);
	WorldGenSetupGrid->changeWidgetBorders(WGSMinimumTargetSize, Border9);

	/*WorldGenSetupGrid->changeWidgetLayout(WGSDoMapSmoothing, tgui::Grid::Layout::Left);
	WorldGenSetupGrid->changeWidgetLayout(WGSDoMapSideSmoothing, tgui::Grid::Layout::Left);
	WorldGenSetupGrid->changeWidgetLayout(WGSHeightTurbulence, tgui::Grid::Layout::Left);
	WorldGenSetupGrid->changeWidgetLayout(WGSSameMoveRestrictions, tgui::Grid::Layout::Left);
	WorldGenSetupGrid->changeWidgetLayout(WGSDirectionRestrictions, tgui::Grid::Layout::Left);

	WGSScrollbar = GuiTheme->load("Scrollbar");
	WGSScrollbar->setSize(25, 700);
	WGSScrollbar->setPosition(WorldGenSetupForm->getPosition() + sf::Vector2f(WorldGenSetupForm->getSize().x, 0));
	WGSScrollbar->setArrowScrollAmount(30);
	WGSScrollbar->setLowValue(60);
	WGSScrollbar->setMaximum(1700);

	WorldGenSetupGrid->hide();
}*/