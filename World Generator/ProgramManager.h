#include "Tileset.h"
#include "GameMap.h"
#include "StaticTextManager.h"
#include "GuiManager.h"
//#include "Globals.h"

class TileShader
{
public:

	TileShader(){};
	~TileShader(){};

	void LoadShaders()
	{
		TileShaderOb.loadFromFile(TileVertexLoc, TileFragmentLoc);

		DefBaseColor.r = 255;
		DefBaseColor.g = 0;
		DefBaseColor.b = 255;

		DefForeColor.r = 255;
		DefForeColor.g = 255;
		DefForeColor.b = 255;
	}
	void ConfigureShaders()
	{
		LoadShaders();

		TileShaderOb.setUniform("TileTexture", TileShaderOb.CurrentTexture);

		TileShaderOb.setUniform("DefBaseColor", sf::Glsl::Vec4(DefBaseColor));
		TileShaderOb.setUniform("DefForeColor", sf::Glsl::Vec4(DefForeColor));

		TileShaderOb.setUniform("BaseColor", sf::Glsl::Vec4(BaseColor));
		TileShaderOb.setUniform("ForeColor", sf::Glsl::Vec4(ForeColor));

		/*shader.setUniform("offset", 2.f);
		shader.setUniform("point", sf::Vector3f(0.5f, 0.8f, 0.3f));
		shader.setUniform("color", sf::Glsl::Vec4(color));          // color is a sf::Color
		shader.setUniform("matrix", sf::Glsl::Mat4(transform));     // transform is a sf::Transform
		shader.setUniform("overlay", texture);                      // texture is a sf::Texture
		shader.setUniform("current", sf::Shader::CurrentTexture);*/

	}
	void SetCurrentColors(sf::Color CurrentBaseColor, sf::Color CurrentForeColor)
	{
		BaseColor.r = CurrentBaseColor.r;
		BaseColor.g = CurrentBaseColor.g;
		BaseColor.b = CurrentBaseColor.b;

		ForeColor.r = CurrentForeColor.r;
		ForeColor.g = CurrentForeColor.g;
		ForeColor.b = CurrentForeColor.b;
	}

	void UpdateVariables()
	{
		TileShaderOb.setUniform("BaseColor", sf::Glsl::Vec4(BaseColor));
		TileShaderOb.setUniform("ForeColor", sf::Glsl::Vec4(ForeColor));
	}

	void UpdateShaderVariables()
	{
		TileShaderOb.setUniform("BaseColor", sf::Glsl::Vec4(BaseColor));
		TileShaderOb.setUniform("ForeColor", sf::Glsl::Vec4(ForeColor));
	}

	sf::Color DefBaseColor;
	sf::Color DefForeColor;

	sf::Color BaseColor;
	sf::Color ForeColor;

	int TileID;
	int ArrayXSize;
	float TileXSize;
	float TileYSize;

	sf::Texture* TileTexture;

	std::string TileVertexLoc = "TileVertex.vert";
	std::string TileFragmentLoc = "TileFragment.frag";

	sf::Shader TileShaderOb;
};

class ProgramManager
{
public:

	ProgramManager() {};
	~ProgramManager() {};

	enum States 
	{
		MainMenu, 
		WorldGenSetup, 
		ProgramSettings, 
		WorldGen, 
		InGame, 
		WorldMap, 
		Running, 
		Paused
	};
	States CurrentState;

	void SetState(States NewState)
	{
		CurrentState = NewState;
	}

	States GetState()
	{
		return CurrentState;
	}

	void ProcessSignal(int SignalID);

	void UpdateShaderVariables(int ArrayXSize, int TileID);
	bool LoadProgramSettings();
	void SaveProgramSettings();
	//void CreateProgramSettings();

	void StartStateManager();
	void ExitMainMenu();
	void EnterMainMenu();
	void EnterWorldGenSettings();
	void ExitWorldGenSettings();
	void OpenProgramSettings();
	void CloseProgramSettings();

	void UpdateWorldGenSettings();
	void SetWorldGenSettings();

	void CommenceWorldGen();
	void ResetWorldGen();
	void EnterWorldGen();
	void ExitWorldGen();

	void SaveWorldGenSettings();
	bool LoadWorldGenSettings();

	//void ConfigureJSONDocs();

	void DrawHeightMap(bool ColorWater);
	void DrawTemperatureMap(bool Greyscale);
	void DrawRainfallMap(bool Greyscale, bool ColorWater);
	void DrawBiomeMap();
	void DrawRegionMap();
	void DrawHeightRegionMap();
	void DrawWaterRegionMap();
	void DrawWindAngleMap();
	void DrawAlternateMapView();

	void BlendMapColors();
	void AdjustMapImageSize();

	void Draw();//Handles Display States.

	void SetupMapSprite();
	void ScaleMapSprite();
	void DisplayWindow();

	void SetTileWindowPositions();
	void DrawTiles();

	void TileDisplayLoop();

	void LoadTileSet();
	void SetupTileSet();

	void ProcessKey(int Key);
	void ChangeDisplayState(int Key);
	void ToggleWorldGenVisibility();

	bool FileExists(std::string FileName);

	bool TileShade;

	void TileShadeOn()
	{TileShade = 1;}
	void TileShadeOff()
	{TileShade = 0;}

	TileShader TShader;
	void TShaderSetBaseColor(int Tile);
	void TShaderSetForeColor(int Tile);
	void TShaderSetTexture(sf::Texture CurrentTexture);

	void SetBaseCenterTile();
	void UpdateMapView(int Key);
	void AdjustZoom(int Direction);
	void UpdateVisibleTiles();

	void StartGame();
	void EnterWorldMapViewer();

	void HandleLeftClick(sf::Vector2f ClickCoordinate);
	void UpdateTileInfo(int Tile);
	void UpdateTileInfo(sf::Vector2f MousePosition);
	void UpdateTileInfoPosition();

	sf::Color GetRandomColor();
	void UpdateFloatingTextPosition();
	void UpdateOverlayName();

	sf::Color GetTileColor(int Position, sf::Image *MapImage);

	void BlendBiomeColors();
	void BlendTileBackgrounds();

	bool DoBlendBiomeMap = true;
	bool DoBlendTileBackgrounds = true;

	float ModifierOne = 0.01f;
	float ModifierTwo = 0.0001f;

	float ModOneAdd = 0.01f;
	float ModTwoAdd = 0.0003f;

	float ModOneMax = 20.0f;
	float ModTwoMax = 0.001f;

	bool UseColorRestraints = true;
	int ColorMinimum = 30;
	int ColorMaximum = 225;

	//UIManager UIMan;
	StaticTextManager STextMan;
	MapSystem::GameMap* CurrentMap;
	MapSystem::WaterRegionManager* CurrentWRM;
	MapSystem::HeightRegionManager* CurrentHRM;
	MapSystem::MapManager MMan;
	GuiManager Gui;

	sf::Texture MenuBackgroundTexture;
	sf::Sprite BackgroundSprite;

	sf::View MapView;

	sf::Image MapImage;
	sf::Texture MapTexture;
	sf::Sprite MapSprite;

	sf::RenderWindow* CurrentWindow;

	std::string TilesetLoc = "Base16Tileset.png";
	Tileset CurrentTileset;//(TilesetLoc, 16, 16, 160, 160);
	sf::Color BaseReplaceColor;//(255, 0, 255);
	sf::Color ForeReplaceColor;//(255, 255, 255);

	json MainConfig;
	json WorldGenConfig;

	//rapidjson::Document ProgramSettingsDoc;
	//rapidjson::Document WorldGenSettingsDoc;

	int WindowWidth;
	int WindowHeight;
	bool Fullscreen;
	int AntiAliasingLevel;
	bool VSync;
	int FramerateLimit;
	bool AutoGL;
	int GLMajor;
	int GLMinor;
	std::string FontLocation;
	std::string GuiConfigLocation;

	sf::Font GlobalFont;

	float MapScaleFactor = 2.3f;

	bool DisplayRiverStartPoints = false;
	bool DisplayAsTiles = true;
	float UIScaleFactor = 1.00f;
	bool WorldGenUIVisible = false;

	float xscalef;
	float yscalef;
	float MapScaledSize = 640.0f;
	int DisplayState = 2; // DISPLAY STATE // 1 = PixelMap 2 = TileMap
	bool ForceGlyphsOnAll = false;

	int WidthInTiles;
	int HeightInTiles;
	int VerticalTileVariation;
	int HorizontalTileVariation;

	int TrueTileWidth; //Amount of tiles to draw horizontally, used if you have less tiles than the amount that the screen could hold.
	int TrueTileHeight;//Amount of tiles to draw vertically, used if you have less tiles than the amount that the screen could hold.

	int CurrentCenterTile;

	int TilesXSize = 16;
	int TilesYSize = 16;

	bool DisplayMap = false;
	bool MapSpriteScaled = false;
	bool ExportMapImages = true;
	float BlendDividend = 1.0f;//////
	int MapMoveDelta = 4;

	int MapCenterCell;
	int TileTypeNumber;

	float ViewDelta = 25.0f;
	float ZoomInDelta = 0.8f; //Never Negative!
	float ZoomOutDelta = 1.2f; //Never Negative!
	float ViewMinimum = 22.0f;
	float ViewMaximum = 200.0f;

	std::vector <int> VisibleTileIDList;

	sf::Vector2f BaseView;

	int CurrentWorldNameCount = 1;
	std::string TempWorldName = "World";
	std::string WorldName;
	std::string Slash = "/";
	std::string End = ".json";
	std::string WorldEnd = ".world";

	sf::Color WaterColor;

	sf::Text TileID;
	sf::Text TileBiome;
	sf::Text TileElevation;
	sf::Text TileRainfall;
	sf::Text TileTemperature;

	sf::Text HelpTip;
	sf::Text CurrentInfoOverlay;

	bool UpdateVisibleTileList = true;
};
