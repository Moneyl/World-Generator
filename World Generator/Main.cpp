//#include "Files.h"
#include "ProgramManager.h"

int main()
{
	ProgramManager ProgMan;
	
	ProgMan.ConfigureJSONDocs();
	ProgMan.LoadProgramSettings();

	sf::RenderWindow MainWindow;
	std::string InputText;
	
	sf::ContextSettings GLContext(0, 0, ProgMan.AntiAliasingLevel, ProgMan.GLMajor, ProgMan.GLMinor);
	if(ProgMan.AutoGL)
	{
		if(ProgMan.Fullscreen)
		{
			MainWindow.create(sf::VideoMode(ProgMan.WindowWidth, ProgMan.WindowHeight), "World Generator 1.0", sf::Style::Fullscreen);
		}
		if(!ProgMan.Fullscreen)
		{
			MainWindow.create(sf::VideoMode(ProgMan.WindowWidth, ProgMan.WindowHeight), "World Generator 1.0", sf::Style::Default);
		}
	}
	if(!ProgMan.AutoGL)
	{
		if(ProgMan.Fullscreen)
		{
			MainWindow.create(sf::VideoMode(ProgMan.WindowWidth, ProgMan.WindowHeight), "World Generator 1.0", sf::Style::Fullscreen, GLContext);
		}
		if(!ProgMan.Fullscreen)
		{
			MainWindow.create(sf::VideoMode(ProgMan.WindowWidth, ProgMan.WindowHeight), "World Generator 1.0", sf::Style::Default, GLContext);
		}
	}

	if(ProgMan.FramerateLimit > 0)
	{
		MainWindow.setFramerateLimit(ProgMan.FramerateLimit);
	}
	MainWindow.setVerticalSyncEnabled(ProgMan.VSync);

	ProgMan.CurrentWindow = &MainWindow;

	ProgMan.UIMan.Initialize(MainWindow);
	ProgMan.UIMan.ConfigureMenus();
	ProgMan.UIMan.ConfigureWorldGenSetup();

	ProgMan.StartStateManager();

	std::cout << "MARKER 1" << std::endl;

	ProgMan.UIMan.MainGenerate->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 1);
	ProgMan.UIMan.MainGenCustom->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 2);
	ProgMan.UIMan.MainSettings->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 10);
	ProgMan.UIMan.MainExit->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 3);
	
	ProgMan.UIMan.WGLeftArrow->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 11);
	ProgMan.UIMan.WGRightArrow->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 12);
	ProgMan.UIMan.WGRegen->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 9);
	ProgMan.UIMan.WGConfig->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 8);
	ProgMan.UIMan.WGMainMenu->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 7);

	ProgMan.UIMan.WGSGenerate->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 4);
	ProgMan.UIMan.WGSMainMenu->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 5);
	ProgMan.UIMan.WGSNew->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 6);//Sets as default
	ProgMan.UIMan.WGSLoad->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 13);
	ProgMan.UIMan.WGSSave->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 14);

	/*ProgMan.UIMan.MenuButton1->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 1);//1-3 in old code.
	ProgMan.UIMan.MenuButton2->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 2);
	ProgMan.UIMan.MenuButton3->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 3);

	ProgMan.UIMan.WGSGenerate->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 4);//10-15 in old code.
	ProgMan.UIMan.WGSMainMenu->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 5);
	ProgMan.UIMan.WGSNew->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 6);
	ProgMan.UIMan.BackToMain->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 7);
	ProgMan.UIMan.BackToSetup->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 8);
	ProgMan.UIMan.RunNewSeed->connect("pressed", &ProgramManager::ProcessSignal, &ProgMan, 9);*/

	bool LogFPS = 0;
	int FPS = 0;
	sf::Clock LoopTimer;
	sf::Time LoopTime;

	std::cout << "MARKER 2" << std::endl;

	while(MainWindow.isOpen())//************** ADD EXCEPTIONS ALL OVER CODE AND MAKE PROPER EXCEPTION LOGGING PLUS OPTIONS TO TOGGLE **************
	{
		sf::Event GameEvent;
		while(MainWindow.pollEvent(GameEvent))
		{
			if(GameEvent.type == sf::Event::Closed)
			{
				MainWindow.close();
			}
			if(GameEvent.type == sf::Event::KeyPressed)
			{
				int Key = GameEvent.key.code;
				ProgMan.ProcessKey(Key);
				//std::cout << Key;
			}
			if(GameEvent.type == sf::Event::MouseWheelMoved)
			{
				ProgMan.AdjustZoom(GameEvent.mouseWheel.delta);
			}
			ProgMan.UIMan.GameGui.handleEvent(GameEvent); //**************//
		}
		if(ProgMan.CurrentState == ProgramManager::WorldGen)
		{
			MainWindow.setView(MainWindow.getDefaultView());
			if(ProgMan.DisplayState == 1)
			{
				//MainWindow.setView(ProgMan.MapView);
				/*sf::Vector2i MousePos = Mouse.getPosition(MainWindow);
				sf::Vector2f WorldPos = MainWindow.mapPixelToCoords(MousePos);
				ProgMan.UpdateTileInfo(WorldPos);*/
			}
		}
		if(ProgMan.CurrentState == ProgramManager::MainMenu)
		{
			MainWindow.setView(MainWindow.getDefaultView());
		}
		
		ProgMan.DisplayWindow();
		if(LogFPS)
		{
			LoopTime = LoopTimer.getElapsedTime();
			if(LoopTime.asSeconds() < 1)
			{
				FPS++;
			}
			else if(LoopTime.asSeconds() >= 1)
			{
				std::cout << "\nFPS: " << FPS;
				FPS = 0;
				LoopTime.Zero;
				LoopTimer.restart();
			}
		}


	}

	return 0;
}
