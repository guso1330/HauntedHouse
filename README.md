# HauntedHouse
My first 3D "game". It is a game where you're trapped in a haunted house and you must find you way out.

Design:
- I decided to go with a FPS style control system. I thought this would be the best way for a player to move around a level that is rendered in 3d.
	
- The first thing I did was implement the debug camera. I had a lot of issues with just getting the camera to show elements on the screen or to render the correct perspective but overall I was able to get the camera working fairly well.

- I also designed to use Autodesk Maya as an implementation tool. This forced me to create an .obj loader class that would allow me to simply pass in .obj models into the game world. This was actually kind of difficult as you had to build the game objects from just a set of points by parsing the file.

- I created three major classes for this project
	1. The mesh class, that was in charge of reading in the .obj data and build a renderable mesh object.
	2. The player class, that was in charge of a user controlled character. It controls it's movement, drawing, and updating.
	3. The object class, which is computer controlled or static game objects. It controls it's own movement, drawing, and updating.

Issues:
- Initially I had a lot of trouble with getting multiple objects rendered to the screen at once. This was due to my lack of full understanding of the vertex array objet and the buffers that go along with it. I envisioned the Player and Object classes to have their own buffers that would handle all of their drawing. One of the draw backs to GLUT is that the C style programming paradigm isn't really compatible with out of scope drawing. The vertex buffers within the classes simply weren't being passed into the main program to be drawn.

- I also ran out of time to implement game logic. I got to caught up in the implementation of a .obj loader, and the debug camera that I wasn't able to create sufficient game logic for 6 or more rooms.

- I also spent ALOT of time trying to implement a 2d collision detection system, but once I detected the collision I had trouble implementing a rigid body solution. Each object basically generates a 2d rectangular area around itself so that it can detect when another object is within it's area. This works, but i wasn't able to develop a system where the objects just wouldn't pass through one another.

- If time had permitted I think abstracting all of the game logic into it's own class would have benificial. I have the utilities class that implements alot of the gamestate functions, but it doens't have enough view into the main file. If I hadn't ran out of time a better implementation for this would be to make a game class that basically handles any of the functionality that would be required to run and maintain the game.