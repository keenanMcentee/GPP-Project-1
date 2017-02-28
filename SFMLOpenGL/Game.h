/// <summary>
/// INCLUDE GUARD TO AVOID HEADER HELL.
/// </summary>
#ifndef GAME_H
#define GAME_H

//All our basic includes to get the project running.
//IOSTREAM TO PRINT TO CONSOLE.
#include <iostream>
//GLEW
#include <GL/glew.h>
#include <GL/wglew.h>
//GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
//DEBUG HEADER TO PRINT TO CONSOLE
#include <Debug.h>
//IMAGE LOADER HEADER
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
//TEXT LOADER HEADERS
#include <sstream>
#include <fstream>
//UI ELEMENTS
#include "Label.h"
#include <SFML\Graphics.hpp>
using namespace std;
using namespace sf;
using namespace glm;

class Game
{
public:
	Game();
	Game(sf::ContextSettings settings);
	~Game();
	void run();
private:
	Label m_lblScore;
	RenderWindow window;
	bool isRunning = false;
	void initialize();
	void update(sf::Time dt);
	void render(sf::Time dt);
	void unload();
	void createProg(GLuint &prog, std::string vertexShaderPath, std::string fragmentShaderPath);
	void readIDs(GLuint &prog);
	void loadTexture(GLuint &texture, std::string fileName);
	void cubeRender(mat4 &model, GLuint &prog, GLuint &texture);
	void barrierRender(mat4 &model, GLuint &prog);
	void playerRender(mat4 &model, GLuint &prog);
	void moveCubes();

	GLuint maxCubes = 100;
	GLuint cubeVbo;
	float count = 0;
	float pushBack = -500;
	mat4 viewMoveLeft, viewMoveRight, viewNormal;
	sf::RectangleShape triangleRect, cubeRect;

	GLuint	vsid,		// Vertex Shader ID
		fsid,		// Fragment Shader ID
		cubeVao = 0,	// Vertex Array ID
		to[1];	// Texture ID 1 to 32
	GLuint positionID,	// Position ID
		colorID,	// Color ID
		textureID,	// Texture ID
		uvID,		// UV ID
		mvpID,		// Model View Projection ID
		timeID,		//ID of the time float in the shader.
		x_offsetID, // X offset ID
		y_offsetID,	// Y offset ID
		z_offsetID;	// Z offset ID
	const int NUM_OF_CUBES = 6;
	mat4 cubeModel[6];
	//const string filename = ".//Assets//Textures//coordinates.tga";
	//const string filename = ".//Assets//Textures//cube.tga";
	//const string filename = ".//Assets//Textures//grid.tga";
	//const string filename = ".//Assets//Textures//grid_wip.tga";
	//const string filename = ".//Assets//Textures//minecraft.tga";
	//const string filename = ".//Assets//Textures//texture.tga";
	//const string filename = ".//Assets//Textures//texture_2.tga";
	//const string filename = ".//Assets//Textures//uvtemplate.tga";
	//const string filename = ".//Assets//Textures//box.tga";
	Font m_ftArial;
	Text scoreOutput;
	float score;
	sf::Clock clock;
	const float FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate;
	sf::RectangleShape a;
	
};

#endif