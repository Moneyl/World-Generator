# World Generator
[![CodeFactor](https://www.codefactor.io/repository/github/moneyl/world-generator/badge)](https://www.codefactor.io/repository/github/moneyl/world-generator)

This project generates a height map and then applies temperature, rainfall, and river simulations to it to form a world map. It represents the final world as a 2D map and has options for multiple map views, including the biome map, heightmap, temperature map, rainfall map, region map, water region map, and more. My original work on this project was in spring of 2015. This was my first major C++ project and when I finally began to understand the language. Keep in mind that because of that, there are many poor code practices in this project such as having massive files and classes instead of splitting them up. 

Note: This project currently won't build, as I am in the process of replacing a few libraries and some old code. See 1.0.0 on the roadmap below for more details. I'll upload a the release with 1.0.0 rather than using an old version from a few years ago.

## Contents
- [Gallery](https://github.com/Moneyl/World-Generator#gallery)
- [Roadmap](https://github.com/Moneyl/World-Generator#roadmap-wip)
- [Libraries used](https://github.com/Moneyl/World-Generator#libraries-used)

## Gallery
![alt text](https://github.com/Moneyl/World-Generator/blob/master/Github%20Images/World_Generator_Sbvg45lKoY.png "Shaded biome map 400x256 world. blue = ocean, dark green = forests, light green = grasslands, sand colored = desert, golden = savannha.")
Shaded biome map for a 400x256 world. blue = ocean, dark green = forests, light green = grasslands, sand colored = desert, golden = savannha. Forests always tend to be on the western sides of mountains since rainfall is calculated west to east. This makes the maps too regular and needs to be improved.

![alt text](https://github.com/Moneyl/World-Generator/blob/master/Github%20Images/World_Generator_8ZgboOAyxh.png "Height map 400x256 world. The brighter the color the higher the elevation.")
Height map for a 400x256 world. The brighter the color the higher the elevation.

![alt text](https://github.com/Moneyl/World-Generator/blob/master/Github%20Images/World_Generator_kmhuLwwyQq.png "Temperature map 400x256 world. Red is warmer, blue is colder.")
Temperature map for a 400x256 world. Red is warmer, blue is colder. The blue spots in the center are a bug, the temperature calculation needs to be improved.

## Roadmap (WIP)
It's been several years since I've worked on this project, and I aim to update it with some new libraries and remedy some of the poor coding practices used. I've listed some of the changes I'd like to make in Todo.txt, but I'll also include them here. The first release will be 1.0.0 as previous versions had no set numbering system. I'll do my best to follow [semantic versioning](https://semver.org/). Keep in mind that this roadmap is subject to change. I won't give any deadlines on when I might complete these as I'm currently more invested in some of my other projects.

### 1.0.0 (In progress - [See branch](https://github.com/Moneyl/World-Generator/tree/1.0.0))
- Replace rapidjson with [Json for modern c++](https://github.com/nlohmann/json)
- Remove boost::lexical_cast requirement as a dependency.
- Update SFML to it's newest version.
- Replace TGUI with [Dear ImGUI](https://github.com/ocornut/imgui). This should include improving the existing gui and providing better help and setting menus.
- Replace simplex noise code with [libnoise](http://libnoise.sourceforge.net/) or one of it's variants, such as [FastNoise](https://github.com/Auburns/FastNoise) or [FastNoise SIMD](https://github.com/Auburns/FastNoiseSIMD). This should allow for much more interesting heightmaps. See [here](https://imgur.com/a/2W9xF0A) for examples on another one of my projects.
- Move all code into /src folder so you don't need to scroll way down to get to the readme on github.

### 1.1.0
- Refactor old code. Split massive .h and .cpp files, rename .h to .hpp, and make sure each class has it's own file rather than bunching several together as they are in GameMap.h. Try to utilize new C++ language features where possible. For an example of how bad it can get check out MapSystem::CalculateRainShadow() or MapSystem::RiverManager::GenerateRivers().
- Replace errors code with exceptions or some other form of error reporting. Returning -1 for errors can be clunky at times.
- Make use of auto iterators and algorithms where possible instead of hand rolling everything as it is now.
- Improve documentation and readme on how to use.
- Replace all uses of rand() with modern c++ methods (std::random_device, std::mt19937, std::uniform_int_distribution, etc). Allows for more control and probably better random number gen. Should also reduce the chance of messing up seeding and other simple things.

### 1.2.0
- Attempt to make map gen more deterministic for a given seed. IIRC there was some excessive use of rand() in situations which didn't require it so a given seed might vary in ways which could be unwanted. Worth examining this validity of this.
- Fix any issues with fonts being blurry or skewed.
- Fix map view scaling or consider replacing each pixel with a small sprite (eg: 8x8 pixels)
- Improve performance of the tile view
- Fix color bugs on biome view
- Improve biome coloring system, consider using hsv hue adjustments rather than fine tuning the existing method.
- Add file selector gui for loading world setting files.
- Allow users to save and load generated maps.
- Store terrain coloring rules in json files.
- See what it'd take to get the world generator to compile with /permissive-

### 1.3.0
- Add basic lua scripting and allow lua scripts to control terrain coloring. Give them access to all of the map data.
- Consider wholly or partially replacing json with lua
- Attempt to improve river pathfinding so there are less failed rivers.

### 1.4.0
- Attempt zoom feature. Allowing you to zoom in closer to the world map and be provided finer details.

### 2.0.0
- Split world generation, map image generation, and gui code into separate projects (Still on the same repo). This way people can easily use the world generation in their own projects and pick which parts they want instead of needed to pull apart all of these different systems.

### 2.1.0
- Split world generation into multiple "modules". Ex: heightmap gen, temperature sim, rainfall sim, river gen, erosion sim, tectonics sim, volcanism sim. Should allow for easier mixing and matching of modules to create unique maps. 

## Libraries Used 
- [Dear ImGui](https://github.com/ocornut/imgui)
- [Json for Modern C++](https://github.com/nlohmann/json)
- [Libnoise](http://libnoise.sourceforge.net/)
