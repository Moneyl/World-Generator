# World Generator
Archived as the code is a big mess and it'd be easier to start from scratch than to clean up this code.

A procedural world generator initially inspired by Dwarf Fortress. This was my first large programming project so the code is pretty bad and has several multi-thousand LOC files, a mess of classes and functions, and poor documentation. I don't plan on working on this again any time soon, just keeping this here as a backup and as a good reminder for myself on how not to design software.

The generator first creates a height map using simplex noise, and then applies temperature, rainfall, and river simulations to it to form a world map. It represents the final world as a 2D map and has options for multiple map views, including the biome map, heightmap, temperature map, rainfall map, region map, water region map, and more.

## Gallery
![alt text](https://github.com/Moneyl/World-Generator/blob/master/Github%20Images/World_Generator_Sbvg45lKoY.png "Shaded biome map 400x256 world. blue = ocean, dark green = forests, light green = grasslands, sand colored = desert, golden = savannha.")
Shaded biome map for a 400x256 world. blue = ocean, dark green = forests, light green = grasslands, sand colored = desert, golden = savannha.

![alt text](https://github.com/Moneyl/World-Generator/blob/master/Github%20Images/World_Generator_8ZgboOAyxh.png "Height map 400x256 world. The brighter the color the higher the elevation.")
Height map for a 400x256 world. The brighter the color the higher the elevation.

![alt text](https://github.com/Moneyl/World-Generator/blob/master/Github%20Images/World_Generator_kmhuLwwyQq.png "Temperature map 400x256 world. Red is warmer, blue is colder.")
Temperature map for a 400x256 world. Red is warmer, blue is colder.
