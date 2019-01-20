//#include "Files.h"
#include "ProgramManager.h"

int main()
{
	ProgramManager Program;

	//Program.ConfigureJSONDocs();
	Program.LoadProgramSettings();
	Program.LoadWorldGenSettings();
	//Program.SetWorldGenSettings();

	sf::RenderWindow MainWindow;
	std::string InputText;
	
	sf::ContextSettings GLContext(0, 0, Program.AntiAliasingLevel, Program.GLMajor, Program.GLMinor);
	if(Program.AutoGL)
	{
		if(Program.Fullscreen)
		{
			MainWindow.create(sf::VideoMode(Program.WindowWidth, Program.WindowHeight), "World Generator 1.0", sf::Style::Fullscreen);
		}
		if(!Program.Fullscreen)
		{
			MainWindow.create(sf::VideoMode(Program.WindowWidth, Program.WindowHeight), "World Generator 1.0", sf::Style::Default);
		}
	}
	if(!Program.AutoGL)
	{
		if(Program.Fullscreen)
		{
			MainWindow.create(sf::VideoMode(Program.WindowWidth, Program.WindowHeight), "World Generator 1.0", sf::Style::Fullscreen, GLContext);
		}
		if(!Program.Fullscreen)
		{
			MainWindow.create(sf::VideoMode(Program.WindowWidth, Program.WindowHeight), "World Generator 1.0", sf::Style::Default, GLContext);
		}
	}

	if(Program.FramerateLimit > 0)
	{
		MainWindow.setFramerateLimit(Program.FramerateLimit);
	}
	MainWindow.setVerticalSyncEnabled(Program.VSync);

	Program.CurrentWindow = &MainWindow;

	Program.UIMan.Initialize(MainWindow);
	Program.UIMan.ConfigureMenus();
	Program.UIMan.ConfigureWorldGenSetup();

	Program.StartStateManager();

	std::cout << "MARKER 1" << std::endl;

	Program.UIMan.MainGenerate->connect("pressed", &ProgramManager::ProcessSignal, &Program, 1);
	Program.UIMan.MainGenCustom->connect("pressed", &ProgramManager::ProcessSignal, &Program, 2);
	Program.UIMan.MainSettings->connect("pressed", &ProgramManager::ProcessSignal, &Program, 10);
	Program.UIMan.MainExit->connect("pressed", &ProgramManager::ProcessSignal, &Program, 3);
	
	Program.UIMan.WGLeftArrow->connect("pressed", &ProgramManager::ProcessSignal, &Program, 11);
	Program.UIMan.WGRightArrow->connect("pressed", &ProgramManager::ProcessSignal, &Program, 12);
	Program.UIMan.WGRegen->connect("pressed", &ProgramManager::ProcessSignal, &Program, 9);
	Program.UIMan.WGConfig->connect("pressed", &ProgramManager::ProcessSignal, &Program, 8);
	Program.UIMan.WGMainMenu->connect("pressed", &ProgramManager::ProcessSignal, &Program, 7);

	Program.UIMan.WGSGenerate->connect("pressed", &ProgramManager::ProcessSignal, &Program, 4);
	Program.UIMan.WGSMainMenu->connect("pressed", &ProgramManager::ProcessSignal, &Program, 5);
	Program.UIMan.WGSNew->connect("pressed", &ProgramManager::ProcessSignal, &Program, 6);//Sets as default
	Program.UIMan.WGSLoad->connect("pressed", &ProgramManager::ProcessSignal, &Program, 13);
	Program.UIMan.WGSSave->connect("pressed", &ProgramManager::ProcessSignal, &Program, 14);

	/*Program.UIMan.MenuButton1->connect("pressed", &ProgramManager::ProcessSignal, &Program, 1);//1-3 in old code.
	Program.UIMan.MenuButton2->connect("pressed", &ProgramManager::ProcessSignal, &Program, 2);
	Program.UIMan.MenuButton3->connect("pressed", &ProgramManager::ProcessSignal, &Program, 3);

	Program.UIMan.WGSGenerate->connect("pressed", &ProgramManager::ProcessSignal, &Program, 4);//10-15 in old code.
	Program.UIMan.WGSMainMenu->connect("pressed", &ProgramManager::ProcessSignal, &Program, 5);
	Program.UIMan.WGSNew->connect("pressed", &ProgramManager::ProcessSignal, &Program, 6);
	Program.UIMan.BackToMain->connect("pressed", &ProgramManager::ProcessSignal, &Program, 7);
	Program.UIMan.BackToSetup->connect("pressed", &ProgramManager::ProcessSignal, &Program, 8);
	Program.UIMan.RunNewSeed->connect("pressed", &ProgramManager::ProcessSignal, &Program, 9);*/

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
				Program.ProcessKey(GameEvent.key.code);
				//std::cout << Key;
			}
			if(GameEvent.type == sf::Event::MouseWheelMoved)
			{
				Program.AdjustZoom(GameEvent.mouseWheel.delta);
			}
			Program.UIMan.GameGui.handleEvent(GameEvent); //**************//
		}
		if(Program.CurrentState == ProgramManager::WorldGen)
		{
			MainWindow.setView(MainWindow.getDefaultView());
			if(Program.DisplayState == 1)
			{
				//MainWindow.setView(Program.MapView);
				/*sf::Vector2i MousePos = Mouse.getPosition(MainWindow);
				sf::Vector2f WorldPos = MainWindow.mapPixelToCoords(MousePos);
				Program.UpdateTileInfo(WorldPos);*/
			}
		}
		if(Program.CurrentState == ProgramManager::MainMenu)
		{
			MainWindow.setView(MainWindow.getDefaultView());
		}
		
		Program.DisplayWindow();
		if(LogFPS)
		{
			LoopTime = LoopTimer.getElapsedTime();
			if(LoopTime.asSeconds() < 1)
			{
				FPS++;
			}
			else if(LoopTime.asSeconds() >= 1)
			{
				//std::cout << "\nFPS: " << FPS;
				FPS = 0;
				LoopTime.Zero;
				LoopTimer.restart();
			}
		}


	}

	return 0;
}
