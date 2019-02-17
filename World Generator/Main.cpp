//#include "Files.h"
#include "ProgramManager.h"

int main()
{
	ProgramManager Program;
	sf::RenderWindow MainWindow;
	std::string InputText;

	Program.LoadProgramSettings();
	Program.LoadWorldGenSettings();

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
	Program.StartStateManager();
	Program.EnterWorldGen();

	sf::Clock LoopTimer;
	sf::Time DeltaTime;
	sf::Time CurrentFrame;
	sf::Time LastFrame;
	sf::Event GameEvent;

	bool DrawDemoWindow = true;
	bool DrawMainMenu = true;
	ImGui::SFML::Init(MainWindow);
	while(MainWindow.isOpen())
	{
		while(MainWindow.pollEvent(GameEvent))
		{
			if(GameEvent.type == sf::Event::Closed)
			{
				MainWindow.close();
			}
			else if(GameEvent.type == sf::Event::KeyPressed)
			{
				sf::Time ProcessKeyStartTime = LoopTimer.getElapsedTime();
				Program.ProcessKey(GameEvent.key.code);
				//std::cout << Key;
			}
			else if(GameEvent.type == sf::Event::MouseWheelMoved)
			{
				Program.AdjustZoom(GameEvent.mouseWheel.delta);
			}
			sf::Time ProcessEventStartTime = LoopTimer.getElapsedTime();
			ImGui::SFML::ProcessEvent(GameEvent);
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

		ImGui::SFML::Update(MainWindow, DeltaTime);
		//Call any gui drawing functions between here and ImGui::EndFrame()
		if (DrawDemoWindow)
		{
			ImGui::ShowDemoWindow(&DrawDemoWindow);
		}

		if (!ImGui::Begin("World Gen Settings", &DrawMainMenu))
		{
			ImGui::End();
		}
		else
		{
			ImGui::InputFloat("Height Octaves", &Program.MMan._octaves, 0.01f, 0.1f, 3);
			ImGui::InputFloat("Height Persistence", &Program.MMan._persistence, 0.01f, 0.1f, 3);
			ImGui::InputFloat("Height Scale", &Program.MMan._scale, 0.01f, 0.1f, 3);

			if (ImGui::Button("Generate"))
			{
				if (Program.CurrentState == ProgramManager::WorldGen)
				{
					Program.ResetWorldGen();
					std::cout << "World Generator Reset" << std::endl;
					Program.CommenceWorldGen();
					std::cout << "World Generator Commenced" << std::endl;
				}
			}

			ImGui::End();
		}
		
		ImGui::EndFrame();
		//End of gui drawing code
		Program.DisplayWindow();

		CurrentFrame = LoopTimer.getElapsedTime();
		DeltaTime = CurrentFrame - LastFrame;
		LastFrame = CurrentFrame;
		//std::cout << "Delta Time: " << DeltaTime.asMilliseconds() << " ms\n";
	}
	ImGui::SFML::Shutdown();

	return 0;
}
